#include <iostream>
#include <vector>

using namespace std;

float revenueCalculate(float);

float billsCalculate(float);

void warnForError(float);

vector<int> getHighestConsumptionCustomers(vector<float>,vector<string>,int);
/*
*/


int main(){

    vector<string> customerCode; //Εδώ αποθηκεύονται οι κωδικοί πελατών
    vector<float> consumption; //Εδώ αποθηκεύεται η κατανάλωση των πελατών

    vector<float> bills;  //Ο λογαριασμός του πελάτη
    vector<float> revenue;//Τα κέρδη της ΕΥΔΑΠ.

    float totalRevenue=0;

    //Είσοδος δεδομένων απο χρήστη.
    while (true){
        string tempCode;
        float tempConsumption;

        cout << endl << "Enter customer code:";
        //Εδώ θα ήταν ιδανικό να έλεγχε το πρόγραμμα αν εισάγει ο χρήστης κωδικούς που έχει εισάγει προηγουμένως.
        cin >> tempCode;
        customerCode.push_back(tempCode);

        do {
            cout << endl << "Enter last quarter's consumption in m^3:";
            cin >> tempConsumption;
        }while(tempConsumption<=0); //ελέγχουμε ο χρήστης να εισάγει θετικές τιμές

        //Checking if values are normal
        if((tempConsumption<20)||(tempConsumption>80)){
            warnForError(tempConsumption);
        }

        consumption.push_back(tempConsumption);
        revenue.push_back( revenueCalculate(tempConsumption) ); //Υπολογισμός με συνάρτηση. Θα μπορούσαμε να ορίσουμε μεταβλητή revenueTemp... (1)
        totalRevenue=totalRevenue+revenueCalculate(tempConsumption);
        bills.push_back(billsCalculate(revenueCalculate(tempConsumption))); //Δες (1) + revenue+revenue*VAT; VAT==20%.



        //Έλεγχος αν ο χρήστης θέλει να εισάγει και άλλες τιμές.
        string resume;
        do{
            cout << endl << "Continue (y or n):";
            cin >> resume;
        }while((resume!="y")&&(resume!="n"));

        if(resume=="y"){continue;}
        else {break;}
    };

    //Πόσους καταναλωτές να εμφανίσει το πρόγραμμα, με την μεγαλύτερη κατανάλωση;
    int howManyToFind;
    cout << "How many top customers to display?" << endl;
    do{
        cout << "Make sure to pick a valid number (0-Customer list length) :";
        cin >> howManyToFind;
    }while ((howManyToFind<0)||(howManyToFind>consumption.size()));

    cout << endl;

    //Βρίσκουμε τους καταναλωτές με την μεγαλύτερη κατανάλωση και αποθηκεύουμε το index τους με φθίνουσα σειρά κατανάλωσης σε ένα νέο Vector.

    //Χρησιμοποιούμε συνάρτηση για τους υπολογισμούς.
    vector<int> topCustomerIndex=getHighestConsumptionCustomers(consumption,customerCode,howManyToFind);

    cout << "============= Customer Rankings =============" << endl;

    for(int i=0;i<howManyToFind;i++){
        cout << i+1 << ". Customer Code:" << "'#" << customerCode[topCustomerIndex[i]] << "'" << " Consumption->" << consumption[topCustomerIndex[i]] << "m^3" << endl;
    };


    cout << "============== Customer Bills ===============" << endl;
    for(int i=0;i<bills.size();i++){
        cout << "Bills of costumer with code #" << customerCode[i] << " are: $"<< bills[i] << endl;
    };


    cout << "=============== EYDAP Revenue ===============" << endl;

    cout << "EYDAP that quarter made a revenue of $" << totalRevenue << endl;

    return 0;
}

void warnForError(float quarterValue){
    cout << "Possible error." << endl;

    if(quarterValue>80){
        float prevConsumption;
        do {
            cout << "Please enter the consumption of the quarter before this one:";
            cin >> prevConsumption;
        }while(prevConsumption<=0);

        if(prevConsumption<20){
            cout << "Please check your water meter!" << endl;
        }
        else if(prevConsumption<40){
            cout << "Possible error." << endl;
        }
    };
};

float revenueCalculate(float consumption){

        float fixedRate=3; //πάγιο
        float drainage=consumption*0.75; //αποχέτευση


        //κέρδη==Πάγιο+Κατανάλωση*Κλίμακα Κατανάλωσης+Αποχέτευση
        if(consumption>0||consumption<16){
            return fixedRate+consumption*0.35+drainage;
        }
        else if(consumption>=16||consumption<61){
            return fixedRate+consumption*0.64+drainage;
        }
        else if(consumption>=61||consumption<86){
            return fixedRate+consumption*1.83+drainage;
        }
        else if(consumption>=86||consumption<111){
            return fixedRate+consumption*2.56+drainage;
        }
        else{ //consumption will be >0
            return fixedRate+consumption*3.2+drainage;
        }
};

float billsCalculate(float revenue){
    float VAT=0.2;
    return revenue+revenue*VAT; //0.2 == 20% VAT.
};

vector<int> getHighestConsumptionCustomers(
    vector<float> const consumption,
    vector<string> const customerCode,
    int howManyToFind
    ){

    vector<float> consumptionTemp=consumption;
    vector<int> highestIndex;

    for(int i=0;i<howManyToFind;i++){
            float tempIndex;
            float tempNum=0;

//          --Ένας πολύ αποδοτικός αλγόριθμος ταξινόμησης :p....
            for(int j=0;j<consumptionTemp.size();j++){

                if (consumptionTemp[j]>=tempNum){
                    tempNum=consumptionTemp[j];
                    tempIndex=j;
                };
            };
            highestIndex.push_back(tempIndex);
            consumptionTemp[tempIndex]=0; //"αφαιρούμε" τον καταναλωτή με την μεγαλύτερη κατανάλωση από την προσωρινή λίστα.
    };

    return highestIndex;

}
