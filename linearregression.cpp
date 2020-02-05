//C++ class for calculating simple linear regression
//Artem Kovera 2020

#include<iostream>
#include<vector>
#include<cassert>
#include<cstdlib>


class LinearRegression
{

private:
    double slope;
    double intercept;
    double meanX;
    double meanY;
    double denominator = 0; 
    double numerator = 0;  
    std::vector<double> mX;
    std::vector<double> mY;
    std::vector<double> xTrain;
    std::vector<double> yTrain;
    std::vector<double> xTest;
    std::vector<double> yTest;
    int vectorSize; 

public:
    
    LinearRegression(std::vector<double> &x, std::vector<double> &y) 
    {
        //the sizes of input vectors must be equal
        assert(x.size() == y.size());
    
        vectorSize = x.size();
        

       mX = std::move(x);
       mY = std::move(y);
    }

//this method applies least squares method for finding cofficients slope and intercept
//in simple linear regression equation y=intercept+slope*x 
    void train () 
    {
        double sumX = 0;
        for(int i = 0; i<vectorSize; i++)
        {
             sumX += mX[i];
        } 
        
        //mean of independent variable x
        meanX = sumX/vectorSize;

        double sumY = 0;

        for(int i = 0; i<vectorSize; i++)
        {
             sumY += mY[i];
        } 
        
        //mean of dependent variable
        meanY = sumY/vectorSize; 

        // making vector of (x[i] - xMean)
        std::vector<double> vec1;
        double temp1;
        for (int i = 0; i < vectorSize; i++) 
        { 
            temp1 = mX[i] - meanX;
            vec1.push_back(temp1);
        } 

        // making vector of (y[i] - yMean)
        std::vector<double> vec2;   
        double temp2;
        for (int i = 0; i < vectorSize; i++) 
        { 
            temp2 = mY[i] - meanY;
            vec2.push_back(temp2);
        }
        
        //finding denominator (sum of squares around mean of independent variable)
        for (int i = 0; i < vectorSize; i++)
        {
            denominator += vec1[i] * vec1[i];
        }

        //finding numerator
        for (int i = 0; i < vectorSize; i++)
        {
            numerator += (vec1[i] * vec2[i]);
        }

        //finding slope
        slope = numerator/denominator;

        //finding intercept
        intercept = meanY - slope * meanX;
        
    };

    double predict (double independentVal) 
    {
        double predictedValue = intercept + slope * independentVal;
        return predictedValue;
    };

};

int main ()
{   
    //simulated example where approximately y = 2 + 3 * x  
    std::vector<double> x {1, 2, 3, 4, 6, 7, 9, 10, 11, 13, 14};
    std::vector<double> y {5, 7, 11, 14, 20, 24, 29, 32, 34, 41, 45};

    
  
    LinearRegression firstLR(x,y);

    firstLR.train();

    std::cout << "predicted value for x=5 is " << firstLR.predict(5) << std::endl; // must be close to 17
    std::cout << "predicted value for x=8 is " << firstLR.predict(8) << std::endl; // must be close to 26
    std::cout << "predicted value for x=15 is " << firstLR.predict(15) << std::endl; // must be close to 47
    std::cout << "predicted value for x=0 is " << firstLR.predict(0) << std::endl; // must be close to 2
  
    return 0;
}