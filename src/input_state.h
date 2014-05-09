#pragma once
#include <array>
#include <stdio.h>

class InputState
{
public:
	InputState(void);
	~InputState(void);

	std::array<bool, 26> letter_keys;
	bool  left, right, up, down;
	bool  space_key;
	bool  mouse_buttons[3];
	float mouse_rot[2];

	bool LetterPressed(char letter)
	{
		return letter_keys.at(tolower(letter) - 'a');
	}

	void SetLetterPressed(char letter, bool val)
	{
		letter_keys.at(tolower(letter) - 'a') = val;
	}

	void PrintLetterKeys(void)
	{
		for(char i = 0; i < 26; i++)
		{
			printf("%c", 'a' + i);
		}
		printf("\n");
		for(bool k : letter_keys)
		{
			printf("%d", k);
		}
		printf("\n");
	}
};

extern InputState g_input_state;

