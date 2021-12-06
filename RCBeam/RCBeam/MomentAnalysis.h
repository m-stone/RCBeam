#pragma once

double NominalMoment(std::shared_ptr<RCBeam>& pRCBeam, 
	std::shared_ptr<Concrete>& pConcrete, 
	std::shared_ptr<Steel>& pSteel);

double MomentEpscm(double eps_cm, 
	std::shared_ptr<RCBeam>& pRCBeam, 
	std::shared_ptr<Concrete>& pConcrete, 
	std::shared_ptr<Steel>& pSteel,
	std::vector<double>& pc_na);

double EquilibriumForces(double c_na,
	double eps_cm,
	std::shared_ptr<RCBeam>& pRCBeam,
	std::shared_ptr<Concrete>& pConcrete,
	std::shared_ptr<Steel>& pSteel,
	std::vector<double>& pfcc,
	std::vector<double>& pfct,
	int num_sxn_layers);

double Beta1(std::shared_ptr<Concrete>& pConcrete);

double epsilon_steel(double c_na, double depth, double eps_cm);

// Fill the zipped vector with pairs consisting of the
// corresponding elements of a and b. (This assumes 
// that the vectors have equal length)
template <typename A, typename B>
void zip(const std::vector<A>& a, const std::vector<B>& b, std::vector<std::pair<A, B>>& zipped)
{
	for (size_t i = 0; i < a.size(); ++i)
	{
		zipped.push_back(std::make_pair(a[i], b[i]));
	}
}

// Write the first and second element of the pairs in 
// the given zipped vector into a and b. (This assumes 
// that the vectors have equal length)
template <typename A, typename B>
void unzip(
	const std::vector<std::pair<A, B>>& zipped,
	std::vector<A>& a,
	std::vector<B>& b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = zipped[i].first;
		b[i] = zipped[i].second;
	}
}