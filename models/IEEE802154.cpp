#include "IEEE802154.hpp"
#include <cmath>
#include <boost/math/special_functions/binomial.hpp>

const std::string Phy_IEEE802154_OQPSK::name = "O-QPSK";
const std::string Phy_IEEE802154_OQPSK::description = "defined in IEEE 802.15.4-2006, pages 267-269";

double Phy_IEEE802154_OQPSK::compute_BER(double sinr) {
	double sum = 0;

	for(int k=2; k<=16; k++)
		sum += pow(-1, k) * boost::math::binomial_coefficient<double>(16, k) * exp(20 * sinr * (1./k - 1.));

	return 8./15 * 1./16 * sum;
}

double Phy_IEEE802154_OQPSK::compute_PER(double sinr, int packetlen) {
	return 1. -  pow(1. - compute_BER(sinr), packetlen);
}

