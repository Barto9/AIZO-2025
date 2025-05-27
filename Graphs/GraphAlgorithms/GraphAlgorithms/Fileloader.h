#pragma once
#include <fstream>
#include <iostream>
class Fileloader
{/* TODO:
	-Load file to array -> i know this shit
	-Save results to file -> check how Chat does it
	I think that's it?
 */
public:
	int* array = nullptr;
	int size = 0;
	int LoadFile(const std::string filename);
	int SaveToFile(const std::string& filename) const;
	void DisplayArray() const;



};

