**Gaussian Process**

Simulate a Gaussian process given its mean and a valid covariance function. The covariance function MUST be symmetric and positive-semidefinite. However, even if a given covariance function has these properties theoretically, the numerically generated covariance matrices might not due to round-off errors.

gaussian.cpp input(s):
   - Final time to simulate, `Tf` (user-input).
   - Number of time points, `N` (user-input).

gaussian.cpp output(s):
   - `gaussian.txt` file with a realization of the process.

*NOTE: If Eigen library is available, `#include <Eigen/Dense>` can be uncommented to provide a "stability" check for the Chelosky decomposition based on the positivity of the eigenvalues of the covariance matrix.*
