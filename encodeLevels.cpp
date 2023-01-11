#include <fstream>
#include <iostream>
#include <string>

#include "data/line.hpp"
#include "data/lineList.hpp"
#include "data/lineListNintendo.hpp"

#include <brotli-cpp.hpp>
#include "data/qrcodegen.hpp"

#include <cstdint>

int32_t binFloat(float x) {
	return *((int32_t*)&x);
}

const char* to_cstr(std::string && s)
{
    static thread_local std::string sloc;
    sloc = std::move(s);
    return sloc.c_str();
}

int curLine;

int main() {
	std::cout << "Starting Generation..." << std::endl;
	std::fstream file;
	for (int i = 0; i < levels; i++) {
		file.open("levels/level" + std::to_string(i) + ".txt", std::fstream::out | std::fstream::trunc);
		file << "Official Level " << (i + 1) << std::endl;
		file << std::hex << (levelEnd[i] - levelStart[i]) << "|" << std::endl;
		for (curLine = levelStart[i]; curLine < levelEnd[i]; curLine++) {
			file << std::hex << binFloat(linelist[curLine]->startX) << "|" 
							 << binFloat(linelist[curLine]->startY) << "|"
							 << binFloat(linelist[curLine]->endX) << "|" 
							 << binFloat(linelist[curLine]->endY) << "|" << std::endl;
		}
		file << std::hex << (koEnd[i] - koStart[i]) << "|" << std::endl;
		for (curLine = koStart[i]; curLine < koEnd[i]; curLine++) {
			file << std::hex << binFloat(linelistKO[curLine]->startX) << "|" 
							 << binFloat(linelistKO[curLine]->startY) << "|"
							 << binFloat(linelistKO[curLine]->endX) << "|" 
							 << binFloat(linelistKO[curLine]->endY) << "|" << std::endl;
		}
		file << std::hex << (liftEnd[i] - liftStart[i]) << "|" << std::endl;
		for (curLine = liftStart[i]; curLine < liftEnd[i]; curLine++) {
			file << std::hex << binFloat(lineListLift[curLine]->startX) << "|" 
							 << binFloat(lineListLift[curLine]->startY) << "|"
							 << binFloat(lineListLift[curLine]->endX) << "|" 
							 << binFloat(lineListLift[curLine]->endY) << "|" << std::endl;
		}
		file << std::hex << (falseEnd[i] - falseStart[i]) << "|" << std::endl;
		for (curLine = falseStart[i]; curLine < falseEnd[i]; curLine++) {
			file << std::hex << binFloat(lineListFake[curLine]->startX) << "|" 
							 << binFloat(lineListFake[curLine]->startY) << "|"
							 << binFloat(lineListFake[curLine]->endX) << "|" 
							 << binFloat(lineListFake[curLine]->endY) << "|" << std::endl;
		}
		file << std::hex << (bgEnd[i] - bgStart[i]) << "|" << std::endl;
		for (curLine = bgStart[i]; curLine < bgEnd[i]; curLine++) {
			file << std::hex << binFloat(linelistBG[curLine]->startX) << "|" 
							 << binFloat(linelistBG[curLine]->startY) << "|"
							 << binFloat(linelistBG[curLine]->endX) << "|" 
							 << binFloat(linelistBG[curLine]->endY) << "|" << std::endl;
		}
		file << std::hex << binFloat(bounds[i][0]) << "|" 
						 << binFloat(bounds[i][1]) << "|"
						 << binFloat(bounds[i][2]) << "|"
						 << binFloat(bounds[i][3]) << "|" << std::endl;
		file << std::hex << binFloat(startPos[i][0]) << "|" 
						 << binFloat(startPos[i][1]) << "|" << std::endl;
		file << std::hex << binFloat(endPoint[i][0]) << "|" 
						 << binFloat(endPoint[i][1]) << "|" << std::endl;
		file.close();
		std::cout << "Level " << (i + 1) << "..." << std::endl;
	}
	std::cout << "Levels Encoded, Starting Compression..." << std::endl;
	for (int i = 0; i < levels; i++) {
		file.open("level" + std::to_string(i) + ".txt", std::fstream::in);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string brotliComp = brotli::compress(buffer.str());
		file.open("levels/level" + std::to_string(i) + ".compressed.txt", std::fstream::out | std::fstream::trunc);
		file << brotliComp;
		file.close();
		std::cout << "Level " << (i + 1) << " text..." << std::endl;
		qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(brotliComp.c_str(), qrcodegen::QrCode::Ecc::LOW);
		
		std::cout << "Level " << (i + 1) << " qr..." << std::endl;
	}
	std::cout << "Done!" << std::endl;
}