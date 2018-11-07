#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class PostFix {
private:
	stack<char> pile;
public:
	void transformerEnPostFix(stack<char> pile);
	bool estUneValeur(char c);
};

bool PostFix::estUneValeur(char c) {
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

void PostFix::transformerEnPostFix(stack<char> pile) {
	string expression;
	cout << "Entrez l'expression infixe à transformer en postfix: " << endl;
	cin >> expression;

	char temp;

	string postfix = "";
	for (int i = 0; i < expression.length; i++)
	{
		if (estUneValeur(expression[i]))
			postfix += expression[i];
		else if (expression[i] == '(')
			pile.push(expression[i]);
		else if (expression[i] == ')')
		{
			temp = pile.top();
			pile.pop();
			while (temp != '(') {
				postfix += temp;

			}

		}
		


	}


}


int main() {




	return 1;
}