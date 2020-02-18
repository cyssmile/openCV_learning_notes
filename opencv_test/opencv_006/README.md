## 图像的位操作
### 1.bitwise_not 取反
取反操作是在原图的基础上，所以not操作有三个参数 第一个是src原图， 第二个是输出的图像， 第三个是mask。mask可以来来做ROI

*** 原图取反***
```
Mat dst1;
bitwise_not(src,dst1,Mat());
imshow("bitwise_not", dst1);
```

*** 图片带ROI 区域的取反***
```
Mat dst2;
Mat mask = Mat::zearos(src.size(),CV_8UC1);
for( int hi =0; hi< mask.rows/2; hi++)
{
    for(int wi =0; wi <mask.cols/2:wi++)
    {
        mask.at<uchar>(hi, wi) =255;
    }
}
bitwise_not(src,dst2,mask);
imshow("bitwise_not_mask",dst2);
```

### bitwise_and 图片的与操作
图片的与操作有四个参数 :原图1 、 与与操作Mat、 输出图像 、mask
*** 原图与 ， 全图为ROI ***
```
Mat dst3;
bitwise_and(src,src,dst3, mat());
imshow("bitwise_and",dst3);
```

*** 原图与 带 ROI区域 ***
```

Mat dst4;
bitwise_and(src,src,dst4, mask;
imshow("bitwise_and",dst4);
```

*** 指定相与的 mat ***
```
Mat dst5;
Mat mask2 = Mat::zearos(src.size(),CV_8UC1);
for( int hi =0; hi< mask2.rows/2; hi++)
{
    for(int wi =0; wi <mask2.cols/2:wi++)
    {
        mask2.at<uchar>(hi, wi) =127;
    }
}
bitwise_and(src,mask2,dst5, mask);
imshow("bitwise_and",dst5);
```

### 或 与或的操作  与 bitwise_and 类似， 有四个参数
```
bitwise_or() 
bitwise_xor()
```