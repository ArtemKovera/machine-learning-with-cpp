//C++ class for calculating simple linear regression
//Artem Kovera 2020

#include<iostream>
#include<vector>
#include<cassert>
#include<cmath>


class LinearRegression
{

private:
    double slope;
    double intercept;
    double meanX;
    double meanY;
    double denominator = 0; 
    double numerator = 0;  
    std::vector<double> xTrain;
    std::vector<double> yTrain;
    std::vector<double> xTest;
    std::vector<double> yTest;
    bool ifTrained = false;

public:
    
    LinearRegression(std::vector<double> &x, std::vector<double> &y) 
    {
        //the sizes of input vectors must be equal
        assert(x.size() == y.size());

        //spliting x input vector into train and test vectors
        //train=75% and test=25% 
        for (int i = 0; i<x.size(); i++)
        {
            if (i%4 != 0)
            {   
                xTrain.push_back(x[i]); 
            }
            else
            {
                xTest.push_back(x[i]);
            }
            
        } 

        //spliting y input vector into train and test vectors
        //train=75% and test=25% 
        for (int i = 0; i<y.size(); i++)
        {
            if (i%4 != 0)
            {   
                yTrain.push_back(y[i]); 
            }
            else
            {
                yTest.push_back(y[i]);
            }
            
        } 
        
    }

//this method applies least squares method for finding cofficients slope and intercept
//in simple linear regression equation y=intercept+slope*x 
    void train () 
    {
        double sumX = 0;
        double sumY = 0;
        int i;
        int size = xTrain.size();

        for(i = 0; i<size; i++) 
        {
           sumX += xTrain[i];     
        } 
        //mean of independent variable x
        meanX = sumX/size;

        for(i = 0; i<size; i++)
        {
             sumY += yTrain[i];
        } 
        //mean of dependent variable
        meanY = sumY/size; 

        // making vector of (xTrain[i] - xMean)
        std::vector<double> vec1;
        for (i = 0; i < size; i++) 
        { 
            vec1.push_back(xTrain[i] - meanX);
        } 

        // making vector of (yTrain[i] - yMean)
        std::vector<double> vec2;   
        for (i = 0; i < size; i++) 
        { 
            vec2.push_back(yTrain[i] - meanY);
        }
        
        //finding the denominator (sum of squares around mean of independent variable)
        for (i = 0; i < size; i++)
        {
            denominator += (vec1[i] * vec1[i]);
        }

        //finding the numerator
        for (i = 0; i < size; i++)
        {
            numerator += (vec1[i] * vec2[i]);
        }

        //finding the slope
        slope = numerator/denominator;

        //finding the intercept
        intercept = meanY - slope * meanX;  

        //setting the flag
        ifTrained = true;
    };

    //method for testing the model
    //returns Root Mean Square Error (RMSE)
    double test ()
    {
        //this method should be used only if the train method has been used already
        assert (ifTrained == true);

        double sum = 0;
        double rmse;
        int i;
        int size = xTest.size();
        std::vector<double> vec;
        vec.reserve(size);

        for (i = 0; i<size; i++)
        {
            vec[i] = predict(xTest[i]);
        }
       
        for (i = 0; i<size; i++)
        {
            sum += pow((vec[i] - yTest[i]), 2);
        }
        
        rmse = sum / size; 
        
        return rmse; 
    }

    double predict (double independentVal) 
    {
        double predictedValue = intercept + slope * independentVal;
        return predictedValue;
    };
    
};

int main ()
{   
    //simulated example where approximately y = 2 + 3 * x  
    std::vector<double> x {1, 2, 3, 4, 6, 7, 9, 10, 11, 13, 14, 15, 16, 17, 18, 20, 22, 23, 25};
    std::vector<double> y {5, 7, 11, 14, 20, 24, 29, 32, 34, 41, 45, 47, 50, 54, 57, 60, 67, 74, 72};

    LinearRegression firstLR(x,y);

    firstLR.train();
    double testValue = firstLR.test();
 
    std::cout << "Root Mean Square Error is " << testValue << std::endl;
    std::cout << "predicted value for x=5 is " << firstLR.predict(5) << std::endl; // must be close to 17
    std::cout << "predicted value for x=8 is " << firstLR.predict(8) << std::endl; // must be close to 26
    std::cout << "predicted value for x=15 is " << firstLR.predict(15) << std::endl; // must be close to 47
    std::cout << "predicted value for x=0 is " << firstLR.predict(0) << std::endl; // must be close to 2
    std::cout << "predicted value for x=30 is " << firstLR.predict(30) << std::endl; // must be close to 92
  
    return 0;
}