#ifndef _BCRDESKEW_H_
#define _BCRDESKEW_H_

#include "Global.h"
#include "opencv2/opencv.hpp"
using namespace cv;

/*
 ************************************************************************
 * Function: Deskew the Image so that the ID card is fine
 *
 * @param  imIn: ����ͼ��
 * @param  len: the length of returned image's larger edge
 * @return  the deskewed ID card image with larger edge's length = len, 
 *			OR an empty image if detect failed
 ************************************************************************
*/
Mat BCRDeskew( const Mat &imIn, int len );



/*
 ************************************************************************
 * Function: ���ͼ�е��ı��α߿�
 *
 * @param  imIn ����ͼ��
 * @param  resOut ��⵽�ı߿�����
 * @return �ɹ�����true��ʧ�ܷ���false
 ************************************************************************
*/
bool DetectQuadrangle(const Mat &imIn, Quadrangle *resOut);


#endif // _BCRDESKEW_H_
