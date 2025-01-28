#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

class EthanolProduction {
private:
    string sugarType;
    string yeastType;
    double sugarAmount;         // in grams
    double yeastAmount;         // in grams
    double fermentationTime;    // in hours
    double distillationTemp;    // in degrees Celsius

    unordered_map<string, double> sugarEfficiency;

    struct YeastInfo {
        double baseEfficiency;
        double optimalFermentationTime;
        double temperatureToleranceMin;
        double temperatureToleranceMax;
    };
    unordered_map<string, YeastInfo> yeastInfo;

    void initSugarEfficiency() {
        sugarEfficiency = {
            {"glucose", 1.2},
            {"sucrose", 1.1},
            {"fructose", 1.3},
            {"maltose", 1.0},
            {"lactose", 0.8}
        };
    }

    void initYeastInfo() {
        yeastInfo = {
            {"Saccharomyces cerevisiae", {1.0, 48, 15, 35}}, 
            {"Kluyveromyces lactis", {0.8, 36, 20, 30}},
            {"Zymomonas mobilis", {1.1, 40, 25, 40}},
            {"Schizosaccharomyces pombe", {0.9, 60, 18, 32}}
        };
    }

    double calculateEfficiency() const {
        double sugarFactor = sugarEfficiency.count(sugarType) ? sugarEfficiency.at(sugarType) : 0.9;
        YeastInfo yeast = yeastInfo.count(yeastType) ? yeastInfo.at(yeastType) : YeastInfo{0.8, 48, 20, 35};
        double yeastFactor = (yeastAmount >= 10 && yeastAmount <= 30) ? yeast.baseEfficiency : 0.6;
        double fermentationFactor = (fermentationTime >= yeast.optimalFermentationTime - 10 &&
                                     fermentationTime <= yeast.optimalFermentationTime + 10) ? 1.3 : 0.7;
        double distillationFactor = (distillationTemp >= yeast.temperatureToleranceMin &&
                                     distillationTemp <= yeast.temperatureToleranceMax) ? 1.2 : 0.5;
        return (sugarFactor * yeastFactor * fermentationFactor * distillationFactor) * 100;
    }

    void suggestYeastOptimization() const {
        if (!yeastInfo.count(yeastType)) {
            cout << " - Invalid yeast type. Please choose a valid yeast.\n";
            return;
        }

        cout << "Suggestions for optimizing ethanol production:" << endl;
        const auto& yeast = yeastInfo.at(yeastType);

        if (distillationTemp < yeast.temperatureToleranceMin || distillationTemp > yeast.temperatureToleranceMax) {
            cout << " - Consider switching yeast type to better match distillation temperature.\n";
        }

        if (fermentationTime < yeast.optimalFermentationTime - 10 || fermentationTime > yeast.optimalFermentationTime + 10) {
            cout << " - Adjust fermentation time closer to the optimal range for this yeast type: "
                 << yeast.optimalFermentationTime << " hours.\n";
        }
    }

public:
    EthanolProduction(const string& sugar, const string& yeast, double sugarAmt, double yeastAmt, 
                      double fermentTime, double distillTemp)
        : sugarType(sugar), yeastType(yeast), sugarAmount(sugarAmt), yeastAmount(yeastAmt), 
          fermentationTime(fermentTime), distillationTemp(distillTemp) {
        initSugarEfficiency();
        initYeastInfo();
    }

    void displayResults() const {
        double efficiency = calculateEfficiency();
        cout << "\nEthanol Production Efficiency Score: " << efficiency << "%" << endl;

        if (efficiency > 100) {
            cout << "Efficiency is optimal! Parameters are well-suited for ethanol production." << endl;
        } else if (efficiency >= 70) {
            cout << "Efficiency is satisfactory, but adjustments could improve yield." << endl;
            suggestYeastOptimization();
        } else {
            cout << "Efficiency is low. Consider optimizing sugar, yeast, fermentation, or distillation parameters." << endl;
            suggestYeastOptimization();
        }
    }
};

bool adminLogin(const string& username, const string& password) {
    const string correctUsername = "admin";
    const string correctPassword = "password123";
    return username == correctUsername && password == correctPassword;
}

void runTestCases(const string& fileName) {
    ifstream testFile(fileName);
    if (!testFile.is_open()) {
        cout << "Error: Could not open test case file!" << endl;
        return;
    }

    struct TestCase {
        string username;
        string password;
        string sugarType;
        string yeastType;
        double sugarAmount;
        double yeastAmount;
        double fermentationTime;
        double distillationTemp;
    };

    string line;
    while (getline(testFile, line)) {
        istringstream iss(line);
        TestCase testCase;
        if (iss >> testCase.username >> testCase.password >> testCase.sugarType >> testCase.yeastType
            >> testCase.sugarAmount >> testCase.yeastAmount >> testCase.fermentationTime >> testCase.distillationTemp) {

            cout << "Running test case with user: " << testCase.username << endl;

            bool loginSuccess = adminLogin(testCase.username, testCase.password);
            if (!loginSuccess) {
                cout << "Access denied. Incorrect credentials.\n";
                continue;
            }

            EthanolProduction production(testCase.sugarType, testCase.yeastType, testCase.sugarAmount, 
                                         testCase.yeastAmount, testCase.fermentationTime, testCase.distillationTemp);

            production.displayResults();
            cout << "\n--- Test Case End ---\n\n";
        }
    }

    testFile.close();
}

void runInteractiveMode() {
    string sugarType, yeastType;
    double sugarAmount, yeastAmount, fermentationTime, distillationTemp;

    cout << "Enter type of sugar component (glucose, sucrose, fructose, maltose, lactose): ";
    cin.ignore();
    getline(cin, sugarType);

    cout << "Enter type of yeast (Saccharomyces_cerevisiae, Kluyveromyces_lactis, Zymomonas_mobilis, Schizosaccharomyces_pombe): ";
    getline(cin, yeastType);

    cout << "Enter amount of sugar in grams: ";
    cin >> sugarAmount;

    cout << "Enter amount of yeast in grams: ";
    cin >> yeastAmount;

    cout << "Enter fermentation time in hours: ";
    cin >> fermentationTime;

    cout << "Enter distillation temperature in degrees Celsius: ";
    cin >> distillationTemp;

    EthanolProduction production(sugarType, yeastType, sugarAmount, yeastAmount, fermentationTime, distillationTemp);
    production.displayResults();
}

int main() {
    string username, password;

    // Admin login
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (!adminLogin(username, password)) {
        cout << "Access denied. Incorrect credentials. Exiting program." << endl;
        return 0;
    }

    while (true) {
        cout << "\n=== Ethanol Production System ===\n";
        cout << "1. Run Test Cases\n";
        cout << "2. Enter Parameters Manually\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string fileName;
            cout << "Enter the test case file name: ";
            cin >> fileName;
            runTestCases(fileName);
        } else if (choice == 2) {
            runInteractiveMode();
        } else if (choice == 3) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
