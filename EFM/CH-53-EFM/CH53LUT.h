#ifndef _CH53_LOOKUP_DATA_
#define _CH53_LOOKUP_DATA_

#include <vector>

namespace CH53
{
    class LUT
    {
    public:
        LUT(const std::vector<double>& data, double min, double max) :
            m_data(data),
            m_min(min),
            m_max(max)
        {
            m_dx = (max - min) / ((double)data.size() - 1);
        }

        double operator()(double value)
        {
            if (m_data.size() == 1)
                return m_data[0];

            double index = (value - m_min) / m_dx;

            int lower = static_cast<int>(floor(index));
            int upper = static_cast<int>(ceil(index));

            if (lower == upper)
                upper++;

            if (lower < 0)
                return m_data.front();
            if (upper >= m_data.size())
                return m_data.back();

            double lowerX = (double)lower * m_dx + m_min;
            double upperX = (double)upper * m_dx + m_min;

            return (value - lowerX) * ((m_data[upper] - m_data[lower]) / (upperX - lowerX)) + m_data[lower];
        }

    private:
        const std::vector<double> m_data;
        double m_dx;
        double m_min;
        double m_max;
    };
}

#endif //_CH53_LOOKUP_DATA_
