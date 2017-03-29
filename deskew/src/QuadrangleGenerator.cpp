/********************************************************************
	����ʱ��:	2014/11/20   11:10
	�ļ���: 	QuadrangleGenerator.cpp
	@author:	���� <hzlipeng@corp.netease.com>
				Copyright (c) 2014, NetEase Inc. All rights reserved.
	
	����:		
*********************************************************************/

#include "Global.h"
#include "QuadrangleGenerator.h"
#include "IntersectionFinder.h"

using namespace std;

/*
 ************************************************************************
 * Function: 
 *
 * @param  leftLine
 * @param  topLine
 * @param  rightLine
 * @param  bottomLine
 * @return 
 ************************************************************************
*/
Quadrangle QuadrangleGenerator::Generate( const Line &leftLine, const Line &topLine, const Line &rightLine, const Line &bottomLine ) const
{
	IntersectionFinder myFinder;

	Quadrangle res;
	res.topLeft     = myFinder.FindIntersection(leftLine, topLine);
	res.topRight    = myFinder.FindIntersection(rightLine, topLine);
	res.bottomLeft  = myFinder.FindIntersection(leftLine, bottomLine);
	res.bottomRight = myFinder.FindIntersection(rightLine, bottomLine);

	return move(res);
}
