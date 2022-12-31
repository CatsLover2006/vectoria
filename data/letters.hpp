class letter {
	public:
		line ** lines;
		int len;
		int size;
		letter(line ** linesIn, const int lenIn, const int sizeIn) {
			size = sizeIn;
			len = lenIn;
			lines = linesIn;
		}
};
extern letter* letters[];
int getIndex(char character);
float getWidth(std::string str, float scale, float weight);
std::string to_str (float t, int accuracy);
std::string to_str (float t);