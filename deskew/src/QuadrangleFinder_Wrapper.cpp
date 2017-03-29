/********************************************************************
	����ʱ��:	2014/11/20   16:42
	�ļ���: 	QuadrangleFinder_Wrapper.cpp
	@author:	���� <hzlipeng@corp.netease.com>
				Copyright (c) 2014, NetEase Inc. All rights reserved.
	
	����:		
*********************************************************************/

#include "Global.h"
#include "QuadrangleFinder_Wrapper.h"
#include "QuadrangleFinder.h"
#include "RawSegmentProcessor.h"
#include "LSD_Wrapper.h"

using namespace std;

string filePathTmp;

void GetCanny(const Mat& _gray, Mat &_canny) 
{
	Mat t;
	//double high_thres = threshold(_gray, thres, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU), low_thres = high_thres * 0.5;
	double scale=1.0;
	double high_thres = 100, low_thres = high_thres*0.75;
	equalizeHist(_gray,t);
	Canny(t, _canny, low_thres/scale, high_thres/scale);
	// �����������͵��ĸ�������ʾ��ֵ���������ֵ�е��е�С��ֵ�������Ʊ�Ե���ӣ������ֵ��������ǿ��Ե�ĳ�ʼ�ָ���һ�����ص��ݶȴ�������ֵ������Ϊ�Ǳ�Ե���أ����С��������ֵ��������������õ���ݶ�������֮������������������ֵ�����ص�����ʱ���ǲű���������ɾ��
#ifdef __DEBUG_MODE__
	imwrite(filePathTmp+".canny.png",_canny);
#endif
}
vector<Line> HoughDetectLines(Mat srcImage){
	Mat gray, canny;
	Mat tmp;
	//resize(srcImage,tmp,Size(800,1400));
	//cvtColor(tmp, gray, CV_BGR2GRAY);
	//resize(srcImage,srcImage,Size(800,1400));
	cvtColor(srcImage, gray, CV_BGR2GRAY);
	GetCanny(gray, canny);

	// extract lines from the edge image
	vector<Vec4i> lines;
	HoughLinesP(canny, lines, 1, CV_PI/180, srcImage.cols*0.2, srcImage.cols*0.2, srcImage.cols*0.1); 
	// HoughLinesP(ͼ, ��, ����ֱ���, �Ƕȷֱ���, ��������Ӧ��ֵ, ��Сֱ�߳���, ���ֱ�߼�϶)
	vector<Line> lineall;
	for(int i=0; i<lines.size(); i++){
		lineall.push_back(Line(Point(lines[i][0],lines[i][1]),Point(lines[i][2],lines[i][3])));
	}
	return lineall;
}

/*
 ************************************************************************
 * Function: 
 *
 * @param  imIn
 * @param  out
 * @return 
 ************************************************************************
*/
void drawlines(Mat im, vector<Line> lines_all, string spath){
	Mat image = im.clone();
	for (int i = 0; i != lines_all.size() ; ++i){
		Scalar color(255,255,0);		
		line(image,Point(lines_all[i].startPoint.x,lines_all[i].startPoint.y),Point(lines_all[i].endPoint.x,lines_all[i].endPoint.y),color,2);
	}
	imwrite(spath, image);
}

bool FindQuadrangle( const Mat &imIn, Quadrangle *out )
{
	LSD_Opts myLSDOpts;
	myLSDOpts.ang_th = 30;
	myLSDOpts.density_th = 0.5;
	myLSDOpts.quant = 1;
	myLSDOpts.scale = 1.0;
	LSD_Wrapper myLSD( myLSDOpts );
	cout<<"detecting lines with LSD..."<<endl;
	vector<Line> lines_all = myLSD.DetectLines(imIn);
	//cout<<"detecting lines with hough..."<<endl;
	//vector<Line> lines_all = HoughDetectLines(imIn);
#ifdef __DEBUG_MODE__
	drawlines(imIn, lines_all, filePathTmp+".line.png"); 
#endif
	ImageInfo info;
	info.kHeight = imIn.rows;
	info.kWidth = imIn.cols;
	RawSegmentProcessor segProcessor(info);

	cout<<"searching for candidates ..."<<endl;
	vector<EdgeCandidate> cands = segProcessor.process(lines_all);
	cout<<"candidates's number is: "<<cands.size()<<endl;
	if(cands.size()>50)
		return false;
	lines_all.clear();

#ifdef __DEBUG_MODE__
	vector<EdgeCandidate> drawCands = cands;
	Mat image1 = imIn.clone();
	for (int i = 0; i != drawCands.size() ; ++i){
		Scalar color(rand()%255,rand()%255,rand()%255,0);		
		for (int j = 0; j != drawCands[i].segments.size() ; ++j){
			line(image1,Point(drawCands[i].segments[j].startPoint.x,drawCands[i].segments[j].startPoint.y),Point(drawCands[i].segments[j].endPoint.x,drawCands[i].segments[j].endPoint.y),color,2);
		}
	}
	imwrite(filePathTmp+".cand.png", image1); 
#endif

	cout<<"searching for quadrangles ..."<<endl;
	QuadrangleFinder myFinder;
	QuadrangleWithCost quad;
	const bool retSuc = myFinder.Find(imIn, cands, &quad);
	(*out) = quad.myQuad;
	return retSuc;

}
