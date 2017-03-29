#ifndef _INTERSECTIONFINDER_H_
#define _INTERSECTIONFINDER_H_

#include "Line_Utils.h"

class IntersectionFinder{
public:
	IntersectionFinder()
	{

	}

	/*
	 ************************************************************************
	 * Function: Ѱ������ֱ�ߵĽ��㡣ע�⣬�ⲿ�豣֤�����߲�ƽ��
	 *
	 * @param  lhs
	 * @param  rhs
	 * @return 
	 ************************************************************************
	*/
	Point FindIntersection(const Line &lhs, const Line &rhs) const;

	/*
	 ************************************************************************
	 * Function: Ѱ������ֱ�ߵĽ��㡣ע�⣬�ⲿ�豣֤�����߲�ƽ��
	 *
	 * @param  theta_lhs
	 * @param  r_lhs
	 * @param  theta_rhs
	 * @param  r_rhs
	 * @return 
	 ************************************************************************
	*/
	Point FindIntersection(const double theta_lhs, const double r_lhs, const double theta_rhs, const double r_rhs) const;


private:
	DISALLOW_CLASS_COPY_AND_ASSIGN(IntersectionFinder);
};



#endif // _INTERSECTIONFINDER_H_
