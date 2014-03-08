#include "ImageResizer.h"
#include "tiff.h"
#include <algorithm>
#include <math.h>
#include <time.h>
#include <iomanip>

extern Tiff *img;
extern Context *ctx;
extern GLubyte checkImage[1024][1024][3];
extern void makeCheckImage(void);

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Resize::execute()
{

    cout<<"Executing Resize Command!"<<endl;


    if(ctx->tiff_hold == false)
    {
        cout<<"Please execute TiffRead before this command!"<<endl;
        return;
    }

    if(fabs(mx - 0.0) < 0.00001){
        cout<<"x_scale is invalid because x scale is too small or equal to 0.0"<<endl;
        return;
    }
    if(fabs(my - 0.0) < 0.00001){
        cout<<"y_scale is invalid because x scale is too small or equal to 0.0"<<endl;
        return;
    }

    int newx = (int)mx * img->mImageWidth;
    int newy = (int)my * img->mImageLength;

    if(fabs(newx) > 1024 || fabs(newy) > 1024){
        cout<<"The x or y is too large"<<endl;
        return;
    }

    //get filter type;

    if(ctx->filter_type == "lanczos"){
        mFilter = new Lanczos();
        mWidth = ctx->filterwidth;
    }else if(ctx->filter_type == "gaussian"){
        mFilter = new Gaussian();
        mWidth = ctx->filterwidth;
    }else if(ctx->filter_type == "mitchell"){
        mFilter = new Mitchell();
        mWidth = 2.0;
    }else if(ctx->filter_type == "hamming"){
        mFilter = new Hamming();
        mWidth = 2.0;
    }else if(ctx->filter_type == "hann"){
        mFilter = new Hann();
        mWidth = 2.0;
    }else if(ctx->filter_type == "triangle" ||ctx->filter_type == "tent"){
        mFilter = new Triangle();
        mWidth = ctx->filterwidth;
    }else if(ctx->filter_type == "box"){
        mFilter = new Box();
        mWidth = ctx->filterwidth;
    }else{
        cout<<"Fail to get filter type!"<<endl;
        return;
    }

    cout<<"The filter is "<<ctx->filter_type<<endl;

    //get border type
    if(ctx->border_type == "zero"){
        mBorder = 0;
    }else if(ctx->border_type == "freeze"){
        mBorder = 1;
    }else if(ctx->border_type == "circular"){
        mBorder = 2;
    }else{
        cout<<"Fail to get border type!";
        return;
    }

    cout<<"The border is "<<ctx->border_type<<endl;

    clock_t start,end;

    start = clock();
    if(mx < 0){
        mx = -mx;
            for(int i = 0; i < img->mImageLength; i++)
            {
                for(int j = 0; j < img->mImageWidth/ 2; j++)
                {
                    swap(img->mImageData[i][j][0],img->mImageData[i][img->mImageWidth - 1 - j][0]);
                    swap(img->mImageData[i][j][1],img->mImageData[i][img->mImageWidth - 1 - j][1]);
                    swap(img->mImageData[i][j][2],img->mImageData[i][img->mImageWidth - 1 - j][2]);
                }
            }
    }

    if(my < 0){
        my = -my;
            for(int i = 0; i < img->mImageWidth; i++)
            {
                for(int j = 0; j < img->mImageLength/ 2; j++)
                {
                    swap(img->mImageData[j][i][0],img->mImageData[img->mImageLength - 1 -j][i][0]);
                    swap(img->mImageData[j][i][1],img->mImageData[img->mImageLength - 1 -j][i][1]);
                    swap(img->mImageData[j][i][2],img->mImageData[img->mImageLength - 1 -j][i][2]);
                }
            }
    }



    //process negative
    int newWidth = fabs(newx);
    int newLength = fabs(newy);

    unsigned char tmpImage[1024][1024][3];



    //process rows
    for(int i = 0; i < img->mImageLength;i++){
        for(int j = 0; j < newWidth; j++){
            for(int c = 0; c < 3; c++){
                float u = j / mx;
                int left, right;
                if(u - mWidth < 0){
                    left = floor(u - mWidth);
                }else{
                    left = floor(u - mWidth) + 1;
                }

                right = floor(u + mWidth);
                float sum = 0;
                float norm = 0;
                for(int k = left; k <= right; k++){

                    short pixel;
                    if(k < 0){
                        switch(mBorder){
                            case 0:
                                pixel = 0;
                                break;
                            case 1:
                                pixel = img->mImageData[i][0][c];
                                break;
                            case 2:
                                pixel = img->mImageData[i][img->mImageWidth - 1 + k][c];
                                break;
                        }
                    }else if(k > img->mImageWidth -1){
                        switch(mBorder){
                            case 0:
                                pixel = 0;
                                break;
                            case 1:
                                pixel = img->mImageData[i][img->mImageWidth - 1][c];
                                break;
                            case 2:
                                pixel = img->mImageData[i][k - img->mImageWidth][c];
                                break;
                        }

                    }else{
                        pixel = img->mImageData[i][k][c];
                    }
                    sum += (float)pixel * mFilter->compute(u - k,mWidth);
                    norm += mFilter->compute(u - k,mWidth);
                }
                sum = sum /norm;
                //cout<<"Norm: " <<norm<<endl;
                //cout<<"Sum :" <<sum<<endl;
                tmpImage[i][j][c] = clamp(sum);

            }
        }
    }


    //process columns
    for(int i = 0; i < newWidth;i++){
        for(int j = 0; j < newLength; j++){
            for(int c = 0; c < 3; c++){
                float u = j / my;
                int up, down;
                if(u - mWidth < 0){
                    up = floor(u - mWidth);
                }else{
                    up = floor(u - mWidth) + 1;
                }

                down = floor(u + mWidth);
                float sum = 0;
                float norm = 0;
                for(int k = up; k <= down; k++){

                    short pixel;
                    if(k < 0){
                        switch(mBorder){
                            case 0:
                                pixel = 0;
                                break;
                            case 1:
                                pixel = tmpImage[0][i][c];
                                break;
                            case 2:
                                pixel = tmpImage[img->mImageLength - 1 + k][i][c];
                                break;
                        }
                    }else if(k > newWidth -1){
                        switch(mBorder){
                            case 0:
                                pixel = 0;
                                break;
                            case 1:
                                pixel = tmpImage[img->mImageLength - 1][i][c];
                                break;
                            case 2:
                                pixel = tmpImage[k - img->mImageLength][i][c];
                                break;
                        }

                    }else{
                        pixel = tmpImage[k][i][c];
                    }
                    sum += (float)pixel * mFilter->compute(u - k,mWidth);
                    norm += mFilter->compute(u - k,mWidth);
                }
                sum = sum /norm;
                img->mImageData[j][i][c] = (GLubyte)clamp(sum);
            }
        }
    }

    img->mImageWidth = newWidth;
    img->mImageLength = newLength;

    end = clock();

    cout<<"The process takes "<<setprecision(5)<< (float)(end -start)/CLOCKS_PER_SEC<<"s"<<endl;

    makeCheckImage();

    //Assign value from tmp array to imageArray.
    for (int i = 0; i < newLength; i++) {
        for (int j = 0; j < newWidth; j++) {
            checkImage[newLength - 1 - i][j][0] = img->mImageData[i][j][0];
            checkImage[newLength - 1 - i][j][1] =img->mImageData[i][j][1];
            checkImage[newLength - 1 - i][j][2] =img->mImageData[i][j][2];
        }
    }

    delete mFilter;
}

/** @brief clamp
  *
  * @todo: document this function
  */
int Resize::clamp(float value)
{
        if(value > 255.0) return 255;
        if(value < 0.0) return 0;
        return (int)value;
}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
 Resize::~Resize()
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 Resize::Resize(float x,float y,float width):mx(x),my(y),mWidth(width),mFilter(0),mBorder(0)
{

}

/** @brief execute
  *
  * @todo: document this function
  */
void Border::execute()
{
    ctx->border_type = border_type;
    cout<<"The border is set to "<< ctx->border_type <<";"<<endl;
}

/** @brief ~Border
  *
  * @todo: document this function
  */
 Border::~Border()
{

}

/** @brief Border
  *
  * @todo: document this function
  */
 Border::Border(string type):border_type(type)
{

}

/** @brief execute
  *
  * @todo: document this function
  */
void Select::execute()
{
    ctx->filter_type = filter_type;
    ctx->filterwidth = width;
     cout<<"The filter is set to "<< ctx->filter_type << " with width "<<ctx->filterwidth<<";"<<endl;
}

/** @brief ~Select
  *
  * @todo: document this function
  */
 Select::~Select()
{

}

/** @brief Select
  *
  * @todo: document this function
  */
 Select::Select(string type):filter_type(type),width(2.0)
{
}
/** @brief Select
  *
  * @todo: document this function
  */
 Select::Select(string type, float width):filter_type(type),width(width)
{

}



