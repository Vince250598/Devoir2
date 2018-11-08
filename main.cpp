#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class PostFix {
private:
	stack<string> pile;
	vector<string> tabPreFix;
	vector<string> tabPostFix;
	stack<string> pileCalcul;
public:
	void transformerEnPostFix(string expression);
	bool estUneValeur(string c);
	int poidsOperateur(string c);
	string evaluerExpressionPostFix(string expression);
	int evaluerOperation(int valeur1, int valeur2, char operateur);
};

int PostFix::evaluerOperation(int valeur1, int valeur2, char operateur) {
	int resultat;

	switch (operateur)
	{
	case '+':
		resultat = valeur1 + valeur2;
		break;
	case '-' :
		resultat = valeur1 - valeur2;
		break;
	case '*' :
		resultat = valeur1 * valeur2;
		break;
	case '/':
		resultat = valeur1 / valeur2;
		break;
	case '%':
		resultat = valeur1 % valeur2;
		break;
	default:
		break;
	}
	return resultat;
}

int PostFix::poidsOperateur(string c) {
	int poids = -1;
	if (c.length() > 1)
	{
		return poids;
	}
	if (c.at(0) == '+' || c.at(0) == '-')
		poids = 1;
	else if (c.at(0) == '*' || c.at(0) == '/' || c.at(0) == '%')
		poids = 2;
	return poids;
}

bool PostFix::estUneValeur(string c) {
	for (int i = 0; i < c.length(); i++)
	{
		if (c.at(i) > 57 || c.at(i) < 48) {
			return false;
		}
	}
	return true;
}

void PostFix::transformerEnPostFix(string expression) {
	int j = 0;
	string element = "";

	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == ' ')
		{
			element = "";
			continue;
		}
		else if(expression[i + 1] == ' ')
		{
			element += expression[i];
			tabPreFix.insert(tabPreFix.begin() + j, element);
			j++;
		}
		else if(i == (expression.length()-1))
		{
			element += expression[i];
			tabPreFix.insert(tabPreFix.begin() + j, element);
		}
		else
		{
			element += expression[i];
		}
	}

	string temp;
	j = 0;

	string postfix = "";
	for (int i = 0; i < tabPreFix.size(); i++) {

		if (poidsOperateur(tabPreFix.at(i)) != -1)
		{
			while (!pile.empty() && pile.top().at(0) != '(' && poidsOperateur(pile.top()) <= poidsOperateur(tabPreFix.at(i)))
			{
				tabPostFix.insert(tabPostFix.begin() + j, pile.top());
				pile.pop();
				j++;
			}
			pile.push(tabPreFix.at(i));
		}
		else if (estUneValeur(tabPreFix.at(i)))
		{
			tabPostFix.insert(tabPostFix.begin() + j, tabPreFix.at(i));
			j++;
		}
		else if (tabPreFix.at(i)[0] == '(')
		{
			pile.push(tabPreFix.at(i));
		}
		else if (tabPreFix.at(i)[0] == ')')
		{
			while (!pile.empty() && pile.top().at(0) != '(')
			{
				tabPostFix.insert(tabPostFix.begin() + j, pile.top());
				j++;
				pile.pop();
			}
			pile.pop();
		}

	}
	while (!pile.empty())
	{
		tabPostFix.insert(tabPostFix.begin() + j, pile.top());
		j++;
		pile.pop();
	}
}

/*string PostFix::evaluerExpressionPostFix(string expression) {
	string resultat;
	char operateur;
	int valeur1;
	int valeur2;

	for (int i = 0; i < expression.length(); i++)
	{
		if (estUneValeur(expression[i])) {
			string s(1, expression[i]);
			pileCalcul.push(s);
		}
		else if (poidsOperateur(expression[i]) != -1)
		{
			valeur1 = stoi(pileCalcul.top());
			pileCalcul.pop();
			valeur2 = stoi(pileCalcul.top());
			pileCalcul.pop();
			string res = to_string(evaluerOperation(valeur2, valeur1, expression[i]));
			pileCalcul.push(res);
		}

	}

	resultat = pileCalcul.top();
	return resultat;
}*/

int main() {
	string expression;
	cout << "Entrez l'expression infixe à transformer en postfix: " << endl;
	getline(cin, expression);

	PostFix post;
	post.transformerEnPostFix(expression);
	

	//cout << "\nResultat PostFix: " << post.evaluerExpressionPostFix(expressionPost) << endl << endl;
	
	system("PAUSE");
	return 1;
}