#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>

void readLabelSourceTXT(std::string fileName);
void readLabelSourceCSV(std::string fileName);
void writeImageWidthHeight(std::string fileName);


int main()
{
	readLabelSourceTXT("label.txt");

	system("pause");
	return 0;
}

void writeImageWidthHeight(std::string fileName)
{
	std::cout << fileName << std::endl;
	//Example of fileName: "image_0001.txt", read the height and width of the image from "image_0001.jpg" and write to the file
	std::fstream imageInfo;
	imageInfo.open("imageInfo.txt", std::ios::out | std::ios::app);

	//Get the height and width of the image
	std::string imageName = fileName.substr(0, fileName.find(".txt")) + ".jpg";
	cv::Mat image = cv::imread(imageName);
	int height = image.rows;
	int width = image.cols;
	//Write the height and width to the file
	imageInfo << height << "\t" << width << "\n";
	std::cout << height << "\t" << width << std::endl;

	imageInfo.close();
}

void readLabelSourceTXT(std::string fileName)
{
	//In each line, contain with format: "newFileName [tab] content of the file(each ";" represent the \n character)"
	std::fstream file;
	file.open(fileName, std::ios::in);
	std::string lineRead;

	while (std::getline(file, lineRead))
	{
		//Create a new file with the name of the first word in the line
		std::string newFileName = lineRead.substr(0, lineRead.find("\t"));
		writeImageWidthHeight(newFileName);
		std::ofstream newFile;
		newFile.open(newFileName, std::ios::out);
		//Write the content of the file, replace each ";" with "\n"
		std::string content = lineRead.substr(lineRead.find("\t") + 1, lineRead.length());
		for (int i = 0; i < content.length(); i++)
		{
			if (content[i] == ';')
			{
				content[i] = '\0';
				newFile << "\n";
			}
			else
			{
				newFile << content[i];
			}
		}

		newFile.close();
	}

	file.close();
}

void readLabelSourceCSV(std::string fileName)
{
	//In each line, contain with format: "newFileName [,] content of the file(each ";" represent the \n character)"
	std::fstream file;
	file.open(fileName, std::ios::in);
	std::string lineRead;
	while (std::getline(file, lineRead))
	{
		//Create a new file with the name of the first word in the line
		std::string newFileName = lineRead.substr(0, lineRead.find(","));
		std::ofstream newFile;
		newFile.open(newFileName, std::ios::out);
		//Write the content of the file, replace each ";" with "\n"
		std::string content = lineRead.substr(lineRead.find(",") + 1, lineRead.length());
		for (int i = 0; i < content.length(); i++)
		{
			if (content[i] == ';')
			{
				content[i] = '\0';
				newFile << "\n";
			}
			else
			{
				newFile << content[i];
			}
		}
		newFile.close();
	}
	file.close();
}