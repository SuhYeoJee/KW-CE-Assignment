//===========================================================//
// https://1coding.tistory.com/154 의 코드를 이용하여 작성함 //
// x64 플랫폼으로 작성 - OpenCV                              //
// opencv_world451d.dll <- debug폴더에 저장                  //
//===========================================================//

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat inputRaw, targetRaw, resultRaw;         // .raw

Mat inputHist, targetHist, resultHist;      // histogram
Mat inputHistimg, targetHistimg, resultHistimg; // histogram image
Mat inputCDF, targetCDF, resultCDF;         //CDF
Mat inputCDFimg, targetCDFimg, resultCDFimg;    //CDF image

Mat inputEQ, targetEQ;      // equalized histogram
Mat LookUpTable;

int resultRow=0, resultCol;

void selectRaw(Mat &openRaw, int* arr);                             //open raw file
void getCDF(Mat& histogram, Mat& CDF, Mat& CDFimg, Mat& histimg);   //get histogram image, cdf, cdf image
void GetResult(void);                                               //make lookuptable, get resultRaw

int  main(void)
{
    int* inputRawArr = NULL;                    //open inout raw file
    cout << "select input raw file" << endl;
    selectRaw(inputRaw, inputRawArr);
    
    int* targetRawArr = NULL;                   //open target raw file
    cout << "select target raw file" << endl;
    selectRaw(targetRaw, targetRawArr);

    int histSize = 255;                         //to get histogram
    float range[] = { 0.0, 255.0 };
    const float* histRange = { range };

    calcHist(&inputRaw, 1, 0, Mat(), inputHist, 1, &histSize, &histRange);  //get input raw histogram
    calcHist(&targetRaw, 1, 0, Mat(), targetHist, 1, &histSize, &histRange);  //get target raw histogram

    getCDF(inputHist, inputCDF, inputCDFimg, inputHistimg);                //get histogrma image, CDF, CDF image
    getCDF(targetHist, targetCDF, targetCDFimg, targetHistimg);

    equalizeHist(inputRaw, inputEQ);                                        //equalize
    equalizeHist(targetRaw, targetEQ);

    GetResult();
    calcHist(&resultRaw, 1, 0, Mat(), resultHist, 1, &histSize, &histRange);  //get result raw histogram
    getCDF(resultHist, resultCDF, resultCDFimg, resultHistimg);               //get histogram image, cdf, cdf image

    //show image, histogram, CDF
    imshow("input", inputRaw);      imshow("inputCDFimg", inputCDFimg),      imshow("inputHistimg", inputHistimg);
    imshow("target", targetRaw);    imshow("targetCDFimg", targetCDFimg),    imshow("targetHistimg", targetHistimg);
    imshow("resultRaw", resultRaw); imshow("resultCDFimg", resultCDFimg),    imshow("resultHistimg", resultHistimg);
    waitKey();

    FILE* outfile = fopen("result.raw", "wb");                  //make result.raw file
    fwrite(resultRaw.ptr<float>(), sizeof(char), resultRow * resultCol, outfile);
    fclose(outfile);

    delete[] inputRawArr;
    delete[] targetRawArr;

    return 0;
}

void selectRaw(Mat &openRaw, int * arr) {
    int sele = 0;                               //select .raw file to open
    cout << "1. babara(512x512).raw" << endl;
    cout << "2. Couple(512x512).raw" << endl;
    cout << "3. gAirplane256_256.raw" << endl;
    cout << "4. gAirplane350_555.raw" << endl;
    cout << "5. gBaboon256_256.raw" << endl;
    cout << "6. gBarbara512_512.raw" << endl;
    cout << "7. gLenna256_256.raw" << endl;
    cout << "select (int): ";
    cin >> sele;

    FILE* fp;
    int rows, cols;
    char rawName[30];

    switch (sele)
    {
    case(1):
        rows = 512; cols = 512;
        strcpy(rawName, "barbara(512x512).raw");
        break;
    case(2):
        rows = 512; cols = 512;
        strcpy(rawName, "Couple(512x512).raw");
        break;
    case(3):
        rows = 256; cols = 256;
        strcpy(rawName, "gAirplane256_256.raw");
        break;
    case(4):
        rows = 555; cols = 350;
        strcpy(rawName, "gAirplane350_555.raw");
        break;
    case(5):
        rows = 256; cols = 256;
        strcpy(rawName, "gBaboon256_256.raw");
        break;
    case(6):
        rows = 512; cols = 512;
        strcpy(rawName, "gBarbara512_512.raw");
        break;
    case(7):
        rows = 256; cols = 256;
        strcpy(rawName, "gLenna256_256.raw");
        break;
    default:
        cout << "input err" << endl;
        exit(1);
        break;
    }
    arr = new int[rows * cols];
    fp = fopen(rawName, "rb");
    fread(arr, rows * cols, 1, fp);
    openRaw = Mat(rows, cols, CV_8UC1, arr);
    fclose(fp);

    if (resultRow == 0) {           //save result size (= input raw size)
        resultRow = rows;
        resultCol = cols;
    }

    cout << "====================" << endl << endl;
    return;
}


void getCDF(Mat& histogram, Mat& CDF, Mat& CDFimg, Mat & histimg) {
    CDF = Mat(histogram.rows, 1, CV_32F, Scalar(0));
    float sum = 0;
    for (int i = 0; i < histogram.rows; i++) {      //get CDF data
        sum += histogram.at<float>(i);
        CDF.at<float>(i) = sum;
    }
    normalize(CDF, CDF, 0, histogram.rows, NORM_MINMAX, -1, Mat());

    int hist_w = 255, hist_h = 255;
    int bin_w = cvRound((double)hist_w / 255);

    CDFimg = Mat(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));         //get cdf image
    histimg = Mat(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));        //get histogram image
    normalize(CDF, CDF, 0, CDFimg.rows, NORM_MINMAX, -1, Mat());
    normalize(histogram, histogram, 0, histimg.rows, NORM_MINMAX, -1, Mat());
    for (int i = 1; i < 255; i++) {
        line(CDFimg, Point(bin_w * (i - 1), hist_h - cvRound(CDF.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(CDF.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
        line(histimg, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
    }

    return;
}

void GetResult(void) {
    int histSize = 256;
    float range[] = { 0.0, 255.0 };
    const float* histRange = { range };
    calcHist(&targetEQ, 1, 0, Mat(), LookUpTable, 1, &histSize, &histRange);

    //================get lookuptable================
    int image_1 = 253;
    int image_2 = 254;

    while (image_1 >= 0) {
        for (int i = targetCDF.at<float>(image_1); i <= targetCDF.at<float>(image_2); i++)
            LookUpTable.at<float>(i) = image_2;
        image_2 = image_1--;
    }
    //================get result=====================
    resultRaw = Mat(inputEQ.size(), inputEQ.type());

    for (int i = 0; i < inputEQ.rows; i++)
        for (int j = 0; j < inputEQ.cols; j++)
            resultRaw.at <uchar>(i, j) = (uchar)LookUpTable.at <float>(inputEQ.at<uchar>(i, j));

    calcHist(&resultRaw, 1, 0, Mat(), resultHist, 1, &histSize, &histRange);  //get result raw histogram

    imshow("resultRaw", resultRaw); waitKey();
}
