#include<iostream>
#include<vector>
#include<string>

class scaleImage {
public:
	scaleImage() {
		
	}
	int Scalewidth;
	int Scaleheight;
	scaleImage(int Iwidth, int Iheight, std::vector<int> screenRes, int scale);
};
scaleImage::scaleImage(int Iwidth,int Iheight, std::vector<int> screenRes, int scale) {
	int PercentageX = scale;//(Iwidth / screenRes[0])+1;
	int PercentageY = scale;//(Iheight/ screenRes[1])+1;
	Scalewidth = PercentageX;
	Scaleheight= PercentageY;
}