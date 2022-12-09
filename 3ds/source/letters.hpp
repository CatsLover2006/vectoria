class letter {
	public:
		const line ** lines;
		int len;
		int size;
		letter(const line ** linesIn, const int lenIn, const int sizeIn) {
			size = sizeIn;
			len = lenIn;
			lines = linesIn;
		}
};

// Letters 
const line* letterA[] = {
	new line(10, -25, 0, 0),
	new line(10, -25, 20, 0),
	new line(5, -12.5, 15, -12.5),
};
const line* letterBL[] = {
	new line(0, -25, 0, 0),
	new line(0, 0, 16, 0),
	new line(20, 0, 16, 0),
	new line(0, -25, 20, -25),
	new line(20, -18, 20, -25),
	new line(20, -8, 20, 0),
	new line(20, -8, 15, -13),
	new line(20, -18, 15, -13),
	new line(0, -13, 15, -13),
};
const line* letterCG[] = {
	new line(0, -20, 0, -5),
	new line(5, -25, 18, -25),
	new line(5, 0, 18, 0),
	new line(5, -25, 0, -20),
	new line(5, 0, 0, -5),
	new line(20, 0, 20, -10),
	new line(12, -10, 20, -10),
	new line(20, -25, 18, -25),
	new line(20, 0, 18, 0),
};
const line* letterD[] = {
	new line(20, -20, 20, -5),
	new line(15, -25, 0, -25),
	new line(15, 0, 0, 0),
	new line(15, -25, 20, -20),
	new line(15, 0, 20, -5),
	new line(0, -25, 0, 0),
};
const line* letterEF[] = {
	new line(0, -25, 0, 0),
	new line(0, -25, 20, -25),
	new line(0, -13, 15, -13),
	new line(0, 0, 20, 0),

};
const line* letterH[] = {
	new line(0, -25, 0, 0),
	new line(18, -25, 18, 0),
	new line(0, -12, 18, -12),

};
const line* letterI[] = {
	new line(8, -25, 8, 0),
	new line(16, -25, 0, -25),
	new line(16, 0, 0, 0),

};
const line* letterJ[] = {
	new line(12, -25, 12, -5),
	new line(20, -25, 4, -25),
	new line(0, -5, 5, 0),
	new line(12, -5, 7, 0),
	new line(5, 0, 7, 0),
};
const line* letterKR[] = {
	new line(0, -25, 0, 0),
	new line(20, -25, 0, -5),
	new line(10, -15, 20, 0),
	new line(0, -25, 20, -25),
};
const line* letterM[] = {
	new line(0, -25, 0, 0),
	new line(25, -25, 12.5, -12.5),
	new line(25, -25, 25, 0),
	new line(0, -25, 12.5, -12.5),
};
const line* letterN[] = {
	new line(0, -25, 0, 0),
	new line(18, -25, 18, 0),
	new line(0, -25, 18, 0),
};
const line* letterOQ[] = {
	new line(20, -20, 20, -5),
	new line(15, -25, 5, -25),
	new line(15, 0, 5, 0),
	new line(0, -5, 5, 0),
	new line(0, -20, 5, -25),
	new line(15, -25, 20, -20),
	new line(15, 0, 20, -5),
	new line(0, -20, 0, -5),
	new line(15, -5, 20, 0),
};
const line* letterP[] = {
	new line(0, -25, 0, 0),
	new line(18, -25, 0, -7),
	new line(0, -25, 18, -25),
};
const line* letterS[] = {
	new line(5, -12.5, 13, -12.5),
	new line(5, -25, 18, -25),
	new line(0, 0, 13, 0),
	new line(5, -25, 0, -20),
	new line(5, -12.5, 0, -17.5),
	new line(0, -17.5, 0, -20),
	new line(13, 0, 18, -5),
	new line(18, -7.5, 13, -12.5),
	new line(18, -5, 18, -7.5)
};
const line* letterT[] = {
	new line(10, -25, 10, 0),
	new line(20, -25, 0, -25),
};
const line* letterU[] = {
	new line(5, 0, 0, -5),
	new line(13, 0, 18, -5),
	new line(5, 0, 13, 0),
	new line(0, -5, 0, -25),
	new line(18, -5, 18, -25),
};
const line* letterV[] = {
	new line(10, 0, 0, -25),
	new line(10, 0, 20, -25),
};
const line* letterW[] = {
	new line(0, 0, 0, -25),
	new line(25, 0, 25, -25),
	new line(0, 0, 12.5, -12.5),
	new line(25, 0, 12.5, -12.5),
};
const line* letterX[] = {
	new line(0, 0, 20, -25),
	new line(0, -25, 20, 0),
};
const line* letterY[] = {
	new line(10, -15, 20, -25),
	new line(0, -25, 10, -15),
	new line(10, -15, 10, 0),
};
const line* letterZ7[] = {
	new line(0, -25, 18, -25),
	new line(18, -25, 0, 0),
	new line(18, 0, 0, 0),
};
const line* letter0[] = {
	new line(20, -20, 20, -5),
	new line(15, -25, 5, -25),
	new line(15, 0, 5, 0),
	new line(0, -5, 5, 0),
	new line(0, -20, 5, -25),
	new line(15, -25, 20, -20),
	new line(15, 0, 20, -5),
	new line(0, -20, 0, -5),
	new line(2.5, -22.5, 17.5, -2.5),
};
const line* letter1[] = {
	new line(5, 0, 5, -25),
	new line(5, -25, 0, -20),
	new line(5, -20, 0, -20),
};
const line* letter2[] = {
	new line(0, -25, 9, -25),
	new line(0, 0, 14, 0),
	new line(9, -25, 14, -20),
	new line(14, -20, 14, -15),
	new line(14, -15, 0, 0),
};

const letter* letters[] = {
	new letter(letterA, 3, 20),
	new letter(letterBL, 9, 20),
	new letter(letterCG, 5, 18),
	new letter(letterD, 6, 20),
	new letter(letterEF, 4, 20),
	new letter(letterEF, 3, 20),
	new letter(letterCG, 9, 20),
	new letter(letterH, 3, 18),
	new letter(letterI, 3, 16),
	new letter(letterJ, 5, 20),
	new letter(letterKR, 3, 20),
	new letter(letterBL, 2, 16),
	new letter(letterM, 4, 25),
	new letter(letterN, 3, 18),
	new letter(letterOQ, 8, 20),
	new letter(letterP, 3, 18),
	new letter(letterOQ, 9, 20),
	new letter(letterKR, 4, 20),
	new letter(letterS, 9, 18),
	new letter(letterT, 2, 20),
	new letter(letterU, 5, 18),
	new letter(letterV, 2, 20),
	new letter(letterW, 4, 25),
	new letter(letterX, 2, 20),
	new letter(letterY, 3, 20),
	new letter(letterZ7, 3, 18),
	new letter(letter0, 9, 20),
	new letter(letter1, 3, 5),
	new letter(letter2, 5, 14),
};

// Char to array index
int getIndex(char character) {
	if (character >= 'A' && character <= 'Z') return character - 'A'; // Caps
	if (character >= 'a' && character <= 'z') return character - 'a'; // Lowercase
	if (character >= '0' && character <= '9') return character - '0' + 26; // Numbers
	return 26; // Backup is 0
}

// Draw String
void drawString(std::string str, float x, float y, float scale, float weight, u32 color) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') x += 23 * scale + weight; // Effectively an A
		else {
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				C2D_DrawLine(letters[getIndex(str.at(i))]->lines[j]->startX * scale + x,
							letters[getIndex(str.at(i))]->lines[j]->startY * scale + y,
							color,
							letters[getIndex(str.at(i))]->lines[j]->endX * scale + x,
							letters[getIndex(str.at(i))]->lines[j]->endY * scale + y,
							color, weight, 0.5f);
			}
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->startX * scale + x,
									letters[getIndex(str.at(i))]->lines[j]->startY * scale + y,
									0.5f, weight/2, color);
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->endX * scale + x,
									letters[getIndex(str.at(i))]->lines[j]->endY * scale + y,
									0.5f, weight/2, color);
			}
			x += (letters[getIndex(str.at(i))]->size + 3) * scale + weight;
		}
	}
}

float getWidth(std::string str, float scale, float weight) {
	float x = 0;
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') x += 23 * scale + weight; // Effectively an A
		else x += (letters[getIndex(str.at(i))]->size + 3) * scale + weight;
	}
	return x;
}