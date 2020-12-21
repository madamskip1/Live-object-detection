#include "BlobDetector.h"
#include <iostream>

void BlobDetector::detect(const cv::Mat &src)
{
    cv::Mat temp;
    src.copyTo(temp);

    std::queue<cv::Point> toCheck;
    int rows = src.rows;
    int cols = src.cols;
    uchar *imgRow;

    uchar *row;
    cv::Point center;

    for (int imgY = 0; imgY < rows; imgY++)
    {
        imgRow = temp.ptr<uchar>(imgY);
        for (int imgX = 0; imgX < cols; imgX++)
        {
            if (imgRow[imgX] == 255)
            {
                std::shared_ptr<Blob> blob = std::make_shared<Blob>();
                toCheck.push(cv::Point(imgX, imgY));
                while (!toCheck.empty())
                {

                    center = toCheck.front();
                    toCheck.pop();
                    blob->add(center.x, center.y);
                    imgRow[center.x] = 0;

                    for (int y = center.y - 1; y <= center.y + 1; y++)
                    {
                        if (y >= 0 && y < rows)
                        {
                            row = temp.ptr<uchar>(y);
                            for (int x = center.x - 1; x <= center.x + 1; x++)
                            {
                                if (x >= 0 && x < cols && row[x] == 255)
                                {
                                    row[x] = 0;
                                    toCheck.push(cv::Point(x, y));
                                }
                            }
                        }
                    }
                }

                blobs.push_back(blob);
            }
        }
    }
}
;

bool BlobDetector::draw(cv::Mat &mat)
{
    for (std::shared_ptr<Blob> blob : blobs)
    {
        if (blob->size() > 250)
        {
            blob->draw(mat);
            auto positionXY = blob->getPosition();
            detection = std::make_tuple(true, positionXY.first,
                                        positionXY.second);
        }
        return true;
    }
    return false;
}

int BlobDetector::numberOfBlobs()
{
    return blobs.size();
}

std::vector<std::shared_ptr<Blob>>& BlobDetector::getBlobs()
{
    return blobs;
}

std::shared_ptr<Blob> BlobDetector::getBlob(int index)
{
    return blobs[index];
}

std::tuple<bool, unsigned, unsigned> BlobDetector::getDetection()
{
    return detection;
}

