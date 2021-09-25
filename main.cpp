#include <bits/stdc++.h>
using namespace std;


// if matirx[i][i] == 0; find a row such that !=0 and swap it.
bool swapRows (vector<vector<double>> &matrix, int &i, int &n, double &ans) {
	for (int j=i+1;j<n;j++) {
		if (matrix.at(j).at(i) !=0) {
			vector<double> temp = matrix.at(j);
			matrix.at(j) = matrix.at(i);
			matrix.at(i) = temp;
			ans *= -1; // when swapping any 2 rows, det*=-1.
			return false;
		}
	}
	return true;
}

double det(vector<vector<double>> matrix) {
	double ans=1, temp;
	int ansLog=0, n, tempInt;
	n = matrix.size();

	for (int i=0;i<n-1;i++){ // row reduction.
		if ( matrix.at(i).at(i) == 0) 
			if ( swapRows(matrix, i, n, ans) ) { // returned true means det is 0
				return 0.0;
			}
		for (int j=i+1;j<n;j++){
				temp = matrix.at(j).at(i) / matrix.at(i).at(i);
			for (int k=i;k<n;k++){  
				matrix.at(j).at(k) -= matrix.at(i).at(k) * temp;
				}
			}
		}


	for (int i=0;i<n;i++) {
		ans *= matrix.at(i).at(i);
		if (ans != 0){
			tempInt = log(abs(ans))/log(10);
			if (tempInt !=0){
				ansLog += tempInt;
				ans/= pow(10,tempInt);
			}
		}

	}		
	return ans*pow(10, ansLog);
}



vector<vector<double>> trimMat(vector<vector<double>> matrix, int x, int y) {
	int sz, p=-1, q=-1;
	sz = matrix.size() -1;
	vector<vector<double>> ans (sz, vector<double>(sz));
	for (int i=0;i<=sz;i++){
		if (i == x) continue;
		p++;q=-1;
		for (int j=0;j<=sz;j++){
			if (j == y) continue;
			q++;
			ans.at(p).at(q) = matrix.at(i).at(j);
		}
	}
	return ans;
}


bool test(vector<vector<double>> matrix, vector<vector<double>> adjugate){
	int n = matrix.size();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			double temp=0;
			for(int k=0;k<n;k++)
				temp += matrix.at(i).at(k) * adjugate.at(j).at(k);
//			cout << temp << endl;
			 if( (i==j&&(temp-1)*(temp-1)>0.000000001)||(i!=j&&temp*temp>0.000000001) ) return false;
		}
	return true;
}


int main(){
	int n;
	cin >> n;
	vector<vector<double>> matrix (n, vector<double>(n));
	vector<vector<double>> adjugate (n, vector<double>(n));
	vector<vector<double>> temp (n-1, vector<double>(n-1));;
	double detVal;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin >> matrix.at(i).at(j);

	detVal = det(matrix);
	if (detVal*detVal < 0.000000001) {
		cout << "{\n\t\"errorMessage\": \"determinantIsZero\"\n}" <<endl;
		return 0;
	}

	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			temp = trimMat(matrix, i, j);
			adjugate.at(i).at(j) = pow(-1, i) * pow(-1, j) * det(temp) / detVal;	
		}

	if (!test(matrix, adjugate)){ // /* to test the answer
		cout << "{\n\t\"errorMessage\": \"debugWarning\",\n\t\"debugMessage\": \"wrongAnswer\"\n}" <<endl;
		return 0;		
	} // test till here */

	cout << "[" <<endl;
	for (int i=0;i<n;i++){
		cout << "\t[";
		for (int j=0;j<n;j++){
			cout << adjugate.at(j).at(i);
			if (j!=n-1) cout << ", ";
		}
		cout << "]";
		if (i!=n-1) cout << "," <<endl;
	}
	cout << endl << "]" <<endl;


	return 0;
}


