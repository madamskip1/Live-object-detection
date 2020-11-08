#include "BlobDetector.h"

void BlobDetector::detect(const cv::Mat& src)
{
	cv::Mat temp;
	src.copyTo(temp);
	int rows = src.rows;
	int cols = src.cols;

	uchar* tempPtr;

	for (int y = 0; y < rows; y++)
	{
		tempPtr = temp.ptr<uchar>(y);

		for (int x = 0; x < cols; x++)
		{
			if (tempPtr[x] == 255)
			{
				// tworzy now¹ plamê, a póŸniej przeszukuje
				std::shared_ptr<Blob> blob = std::make_shared<Blob>();
				blobSearch(blob, temp, x, y);
				blobs.push_back(blob);
			}
		}
	}
};

void BlobDetector::blobSearch(std::shared_ptr<Blob> blob, cv::Mat& mat, int x, int y)
{
	if (!(x >= 0 && x < mat.cols && y >= 0 && y < mat.rows))
		return;

	uchar* ptr;
	ptr = mat.ptr<uchar>(y);

	if (ptr[x] == 255)
	{
		blob->add(x, y);
		ptr[x] = 0;

		blobSearch(blob, mat, x + 1, y); // kolejna kolumna
		blobSearch(blob, mat, x - 1, y); // poprzednia kolumna
		// poprzedni wiersz
		blobSearch(blob, mat, x - 1, y - 1);
		blobSearch(blob, mat, x, y - 1);
		blobSearch(blob, mat, x + 1, y - 1);
		// nastêpny wiersz
		blobSearch(blob, mat, x - 1, y + 1);
		blobSearch(blob, mat, x, y + 1);
		blobSearch(blob, mat, x + 1, y + 1);
	}
};

void BlobDetector::draw(cv::Mat& mat)
{
	for (std::shared_ptr<Blob> blob : blobs)
	{
		if (blob->size() > 500)
		{
			blob->draw(mat);
		}
	}
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
