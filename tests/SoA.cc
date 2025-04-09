#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>

#include "SoALayout.h"
#include "PortableHostCollection.h"
#include "PortableCollection.h"

GENERATE_SOA_LAYOUT(SoATemplate,
                    SOA_COLUMN(float, x),
                    SOA_COLUMN(double, y),
                    SOA_COLUMN(double, z),
                    SOA_EIGEN_COLUMN(Eigen::Vector3d, a),
                    SOA_SCALAR(int, detectorType))

using SoA = SoATemplate<>;
using SoAView = SoA::View;
using SoAConstView = SoA::ConstView;

void print(SoAView v) {
    for (int i = 0; i < v.metadata().size(); ++i) {
        std::cout << "x: " << v[i].x() << ", y: " << v[i].y() << ", z: " << v[i].z() << ", a: " << v[i].a().transpose()
                  << std::endl;
    }

    std::cout << "detectorType: " << v.detectorType() << std::endl;
    std::cout << "size: " << v.metadata().size() << std::endl;
}

int main() {
    int elements = 10;
    alpaka::DevCpu const& host = alpaka::getDevByIdx(alpaka::PlatformCpu{}, 0);
    PortableCollection<SoA, alpaka::DevCpu> collection(elements, host);
    SoAView view = collection.view();
    // Fill the SoA 
    for (int i = 0; i < view.metadata().size(); ++i) {
        view[i].x() = static_cast<float>(i);
        view[i].y() = static_cast<double>(i) * 2.0;
        view[i].z() = static_cast<double>(i) * 3.0;
        view[i].a() = Eigen::Vector3d(static_cast<double>(i), static_cast<double>(i), static_cast<double>(i));
    }
    view.detectorType() = 42;   

    // Print the SoA
    print(view);
}