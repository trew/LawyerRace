namespace positionHelper { 
	inline float centerHorizontal(const float _leftBorder, const float _rightBorder, const float _width) {
		return (_rightBorder - _leftBorder) / 2 - _width / 2 + _leftBorder;
	}

	inline float centerVertical(const float _topBorder, const float _bottomBorder, const float _height) {
		return (_bottomBorder - _topBorder) / 2 - _height / 2 + _topBorder;
	}
	
	inline float leftAlign(const float _leftBorder, const float _leftMargin) {
		return _leftMargin + _leftBorder;
	}
	
	inline float rightAlign(const float _rightBorder, const float _rightMargin, const float _width) {
		return (_rightBorder - _rightMargin - _width);
	}
	
	inline float topAlign(const float _topBorder, const float _topMargin) {
		return _topMargin + _topBorder;
	}
	
	inline float bottomAlign(const float _bottomBorder, const float _bottomMargin, const float _height) {
		return _bottomBorder - _bottomMargin - _height;
	}
}