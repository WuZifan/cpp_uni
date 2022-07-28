#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "dltools.h"
#include <vector>
#include <FreeImage.h>
#include <string>
#include <fstream>

cv::Mat bitMap2Mat(FIBITMAP* fiBmp, const FREE_IMAGE_FORMAT &fif)
    {
        if (NULL == fiBmp || FIF_GIF != fif)
            return cv::Mat();
        int width = FreeImage_GetWidth(fiBmp);
        int height = FreeImage_GetHeight(fiBmp);

        BYTE intensity;
        BYTE* pIntensity = &intensity;
        if(FreeImage_GetBPP(fiBmp) !=8)
            fiBmp = FreeImage_ConvertTo8Bits(fiBmp); //必须转化为8bit
        RGBQUAD* pixels = new RGBQUAD; 
        pixels = FreeImage_GetPalette(fiBmp);
        cv::Mat img=cv::Mat::zeros(height, width, CV_8UC3);

        uchar* p;
        for (int i = 0; i < height; i++)
        {
            p = img.ptr<uchar>(i);
            for (int j = 0; j < width; j++)
            {
                FreeImage_GetPixelIndex(fiBmp, j, i, pIntensity);
                p[3 * j] = pixels[intensity].rgbBlue;
                p[3 * j + 1] = pixels[intensity].rgbGreen;
                p[3 * j + 2] = pixels[intensity].rgbRed;
            }
        }

        return img;
    }

int gif2Mat(char* data, size_t dataSize, std::vector<cv::Mat>& gifImgs, cv::Mat& singleImg)
    {
        /* initialise
        ->open memory
        ->getImageType
        ->load bitmaps
        ->bitmaps to Mat
        ->free all resource
        */
        // condition1: data is not null
        if (NULL == data || dataSize == 0)
            return -1;
        FreeImage_Initialise();
        FIMEMORY* memory = FreeImage_OpenMemory((BYTE*)data, dataSize);
        if (NULL==memory)
        {
            FreeImage_DeInitialise();   //condition 2: memory is not null
        }

        FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(memory);
        if (FIF_UNKNOWN == fif)    //condition 3: type of image should be know
        {
            fprintf(stderr, "unknown type of image");
            if (NULL != memory) FreeImage_CloseMemory(memory);
            FreeImage_DeInitialise();
            return -1;
        }
        else if (FIF_GIF != fif)  //condition 4: type of image should be GIF
        {
            if (NULL != memory) FreeImage_CloseMemory(memory);
            FreeImage_DeInitialise();
            return 0;
        }

        FIMULTIBITMAP * fiBmp = FreeImage_LoadMultiBitmapFromMemory(fif, memory, GIF_DEFAULT);
        if (NULL==fiBmp)
        {
            if (NULL != memory) FreeImage_CloseMemory(memory);   //condition 5: bitmaps is not null
            FreeImage_DeInitialise();
            return -1;
        }

        int num = FreeImage_GetPageCount(fiBmp);

        for (int i = 0; i < num; i++)
        {
            if (i==0 || i==2)
            {
                FIBITMAP *mfibmp = FreeImage_LockPage(fiBmp, i);
                if (mfibmp)
                {
                    cv::Mat dst = bitMap2Mat(mfibmp, fif);
                    FreeImage_UnlockPage(fiBmp, mfibmp, false);
                    if (dst.empty())
                    {
                        if (NULL != memory) FreeImage_CloseMemory(memory);
                        if (NULL != fiBmp) FreeImage_CloseMultiBitmap(fiBmp, GIF_DEFAULT);
                        FreeImage_DeInitialise();
                        return -1;
                    }
                    gifImgs.push_back(dst);
                    dst.release();
                }
            }
        }

        if (NULL != memory)
            FreeImage_CloseMemory(memory);
        if (NULL != fiBmp)
            FreeImage_CloseMultiBitmap(fiBmp);
        FreeImage_DeInitialise();

        return 0;
    }

int main(){
    std::string file_name = "/Users/zifanwu/VSCodeProjects/cpp_uni/cmake_learn/project1/data/test.gif";
    std::ifstream in(file_name,std::ios_base::in | std::ios_base::binary);
    if(!in){return EXIT_FAILURE;}

    char* data;
    in>>data;


    // gif2Mat

    

}
