/*********************************************************************************************************
 File Name     : MP_SISON.c
 
 Author        : Danielle Kirsten T. Sison
 Section       : S12B
 Last Modified : Nov. 30, 2018
 Submitted to  : College of Computer Studies, DLSU-Manila
 
 About: This program computes for the annual tax due under the 2017 Tax Code and TRAIN Law, and your
 take-home income. It assumes that user is an employed individual working at a private institution.
 
 Disclaimer: The program output is just an approximation of the tax due and by no means the exact value.
 Note: 2017 Tax Code is the same as NIRC 1997, and 2018 Tax Code is the same as TRAIN Law.
 **********************************************************************************************************/
#include <stdio.h>

double newcode(double annual, double *basic, double *excess);

/* Function Name: pattern
 Description: It receives a character and loops it to make a linear design
 Parameters:
 design - character to be printed
 number - number of times character will be printed */
void pattern(char design, int number)
{
    int i;
    for (i=0; i<= number; i++)
    {
        printf("%c", design);
    }
    printf("\n\n");
}

/* Function Name: SSS
 Description: Gets the monthly credit of SSS contribution
 Parameter:
 monthly - monthly salary of user
 Return Value:
 It returns the monthly credit in integer value */
int SSS(double monthly)
{
    if (monthly < 1000)
        return 0;
    if (monthly > 15750)
        return 32; // As 32 * 500 = 16,000 and 16,000 is the ceiling of the SSS table
    return ((monthly + 250)/500);
}

/* Function Name: PHealth
 Description: Gets the monthly base of PHealth contribution
 Parameter:
 monthly - monthly salary of user
 pointer - identification whether to use 2018 or 2017 contribution calculation
 Return Value:
 It returns the monthly base in integer value */
int PHealth (double monthly, int pointer)
{
    if (pointer == 2018) {  //Calculation for 2018 monthly credit
        if (monthly <= 10000)
            return 10000;
        else if(monthly >= 40000)
            return 40000;
        else
            return monthly;
    }
    else {  // Calculation for 2017 monthly base
        if (monthly <= 8999.99)
            return 8;
        else if(monthly >= 35000)
            return 35;
        else
            return monthly/1000;
    }
}

/* Function Name: PagIbig
 Description: Computes for the monthly Pag-Ibig contribution
 Parameter:
 monthly - monthly salary of user
 Return Value:
 It returns the monthly Pag-Ibig contribution */
double PagIbig(double monthly)
{
    if (monthly < 5000)
    {
        if(monthly < 1500)
            return monthly * 0.01;
        else
            return monthly * 0.02;
    } else
        return 100.00;
}

/* Function Name: oldcode
 Description: Gets the value to be added and percent to be
 multiplied to the excess depending on the bracket the annual
 taxable net income falls into (Based on 2017 annual income tax table)
 Parameters:
 annual - computed annual taxable net income
 basic - the operand of a corresponding a bracket to be added
 excess - corresponding percent of excess of a bracket
 lowerbound - the lowerbound of the range of a bracket
 Return Value:
 Lowerbound to be subtracted to the annual taxable net income */
double oldcode(double annual, double *basic, double *excess)
{
    double lowerbound = 0;
    
    if(annual > 500000)
    {
        lowerbound = 500000;
        *excess = 0.32;
        *basic = 125000;
    }
    else if (annual > 250000 && annual <= 500000)
    {
        lowerbound = 250000;
        *excess = 0.30;
        *basic = 50000;
    }
    else if (annual > 140000 && annual <= 250000)
    {
        lowerbound = 140000;
        *excess = 0.25;
        *basic = 22500;
    }
    else if (annual > 70000 && annual <= 140000)
    {
        lowerbound = 70000;
        *excess = 0.2;
        *basic = 8500;
    }
    else if (annual > 30000 && annual <= 70000)
    {
        lowerbound = 30000;
        *excess = 0.15;
        *basic = 2500;
    }
    else if (annual > 10000 && annual <= 30000)
    {
        lowerbound = 10000;
        *excess = 0.1;
        *basic = 500;
    }
    
    return lowerbound;
}

/* Function Name: newcode
 Description: Gets the value to be added and percent to be
 multiplied to the excess depending on the bracket the annual
 taxable net income falls into (Based on TRAIN annual income tax table)
 Parameters:
 annual - computed annual taxable net income
 basic - the operand of a corresponding a bracket to be added
 excess - corresponding percent of excess of a bracket
 lowerbound - the lowerbound of the range of a bracket
 Return Value:
 Lowerbound to be subtracted to the annual taxable net income */

double newcode(double annual, double *basic, double *excess)
{
    double lowerbound = 250000;
    
    if (annual > 8000000)
    {
        lowerbound = 8000000;
        *basic = 2410000;
        *excess = 0.35;
    }
    else if (annual > 2000000 && annual <= 800000)
    {
        lowerbound = 2000000;
        *basic = 490000;
        *excess = 0.32;
    }
    else if (annual > 800000 && annual <= 2000000)
    {
        lowerbound = 800000;
        *basic = 130000;
        *excess = 0.30;
    }
    else if (annual > 400000 && annual <= 800000)
    {
        lowerbound = 400000;
        *basic = 30000;
        *excess = 0.25;
    }
    
    return lowerbound;
}

/* Function Name: personal
 Description: Computes for annual personal exemption
 Parameters:
 kids - number of kids user declared (0 to 4)
 decAdd - user decision whether spouse already declared
 the 50000 personal exemption
 Return Value:
 It returns the total personal exemption of the user*/
double personal(int kids)
{
    return kids * 25000 + 50000; // Single or Married
}

/* Function Name: taxNetIncome
 Description: Computes for annual taxable net income
 Parameters:
 personal - total personal exemption
 deductions - sum of Pag-Ibig, SSS, and PhilHealth annual contribution
 thirteenpay - 13th month pay
 pointer - identification whether to use 2017 or 2018 limit of non-taxables
 Return Value:
 It returns the computed taxable net income */
double taxNetIncome(double personal, double deductions, double monthly, double thirteenpay, int pointer)
{
    if (pointer == 2017)
        if (thirteenpay < 82000)
            return monthly * 12 - deductions - personal;
        else
            return monthly * 12 + 82000 + (thirteenpay - 82000) - (deductions + 82000) - personal;
        else
            if (thirteenpay < 90000)
                return monthly * 12 - deductions;
            else
                return monthly * 12 + 90000 + (thirteenpay - 90000) - (deductions + 90000); 
}

/* Function Name: oldtax/trainlaw
 Description: Computes for annual tax due under the 2017 Tax Code/Train Law
 Parameters:
 monthly - monthly salary of user
 personal - total personal exemption
 deductions - sum of Pag-Ibig and SSS monthly contribution
 thirteen - 13th month pay
 fPhilHlth - decision of user whether voluntary or involuntary
 Functions involved:
 Phealth, taxNetIncome
 Return Value:
 Computed annual tax due
 */
double oldtax(double monthly, double personal, double deductions, double thirteenpay, double fPhilHlth)
{
    double fTaxableNetIncome,fLowBound = 0, fExcess = 0, fBasic = 0;
    int pointer = 2017;
    
    //Compute for 2017 PhilHealth
    if (fPhilHlth == 1)
        if (monthly < 25000)
            fPhilHlth = 200; // Voluntary member pays fixed P200 if monthly salary is less than P25k
        else
            fPhilHlth = 300; // Voluntary member pays fixed P300 if monthly salary is more than P25k
        else
            fPhilHlth = PHealth(monthly, pointer) * 1000 * 0.025 / 2; // Employee Share is half of the 2.5% of monthly credit
    
    deductions = (deductions + fPhilHlth) * 12; // Computes for annual total contribution
    fTaxableNetIncome = taxNetIncome(personal, deductions, monthly, thirteenpay, pointer);
    //Getting the Lower Bound, Percent of Excess, fBasic
    if (fTaxableNetIncome > 10000)
        fLowBound = oldcode(fTaxableNetIncome,&fBasic, &fExcess);
    else
        fExcess = 0.05;
    return (fTaxableNetIncome - fLowBound) * fExcess + fBasic;
}

// Computes for annual tax due under TRAIN Law
double trainlaw(double monthly, double deductions, double thirteen, double personal, double fPhilHlth)
{
    double fTaxableNetIncome, fExcess = 0.20, fBasic = 0, fLowBound = 0;
    int pointer = 2018;
    
    //Compute for 2018 PhilHealth
    if(fPhilHlth == 1) {
        if (monthly < 25000)
            fPhilHlth = 200; // Voluntary member pays fixed P200 if monthly salary is less than P25k
        else
            fPhilHlth = 300; } // Voluntary member pays fixed P300 if monthly salary is more than P25k
    else
        fPhilHlth = PHealth(monthly, pointer) * 0.0275 / 2; // Employee Share is half of the 2.75% of monthly credit
    deductions = (deductions + fPhilHlth) * 12; // Computes for total annual contribution
    //Compute Annual Taxable Net Income and Check for Excess of Non-Taxables
    fTaxableNetIncome = taxNetIncome(personal, deductions, monthly, thirteen, pointer);
    //Getting the Lower Bound, Percent of Excess, and fBasic
    
    fLowBound = newcode(fTaxableNetIncome, &fBasic, &fExcess);
    return (fTaxableNetIncome - fLowBound) * fExcess + fBasic;
}

/* Main Function Variables and Definitions:
 fMonthly - monthly income
 fOld/fNew - annual income tax due for 2017/2018 tax code
 fPersonal - computed total personal exemption
 fThirteen - thirteenth month pay
 fOther - other sources of income
 fDeductions - sum of SSS and Pag-Ibig contribution
 fSocial - decision whether voluntary or non-voluntary sss member
 - computed monthly SSS contribution;
 fPbig - decision whether voluntary or non-voluntary Pag-Ibig member;
 - computed monthly SSS contribution;
 fPhilHlth - decision whether voluntary or non-voluntary PhilHealth member;
 - computed monthly PhilHealth contribution
 nKids - no. of dependents
 nCivil - civil status
 nDecKids - decision whether spouse declared dependents or not
 counter - loop counter for other sources of income
 source - decision whether user has other sources of income or not */
int main()
{
    double fMonthly = 0,fOld = 0, fNew =0, fPersonal = 0, fThirteen = 0, fOther = 1, fDeductions = 0;
    double fSocial = 0, fPbig = 0, fPhilHlth = 0;
    int nKids, nCivil, nDecKids = 0, counter = 0, source;
    
    pattern('#', 51);
    printf("   ❖ WELCOME TO THE TAX CALCULATOR FOR DUMMIES ❖\n"); printf("\n");
    pattern('#', 51);
    printf("✖︎ Please DO NOT enter words or letters as an input ✖︎"); printf("\n\n");
    
    do{
        printf("Enter monthly salary: "); scanf("%lf",&fMonthly); printf("\n");
    } while(fMonthly < 0);
    
    pattern('~', 51);
    printf("          [1] Single         [2] Married\n"); printf("\n");
    do{
        printf("Civil Status: "); scanf("%d", &nCivil); printf("\n");
    } while(nCivil < 1 || nCivil > 2);
    do{
        printf("No. of Dependents: "); scanf("%d", &nKids); printf("\n");
        if(nKids < 0 || nKids > 4)
            printf("Only 0 to 4 dependents can be declared.\n\n");
    } while(nKids < 0 || nKids > 4);
    
    if(nCivil == 2 && nKids!= 0)
    {
        pattern('~', 51);
        printf("          [1] Yes         [2] No\n"); printf("\n");
        do{
            printf("Did your spouse declare the dependents?: "); scanf("%d", &nDecKids);
        } while(nDecKids < 1 || nDecKids > 2); printf("\n\n");
        if(nDecKids == 1)
            nKids  = 0; // User won't get additional personal exemption if spouse declared kids
        
    }
    
    pattern('~', 51);
    printf("                  CONTRIBUTIONS \n\n");
    printf("     [0] if not voluntary and [1] if voluntary\n\n");
    do{
        printf("SSS: "); scanf("%lf", &fSocial);
    } while(fSocial < 0 || fSocial > 1);
    do {
        printf("\nPag-Ibig: "); scanf("%lf", &fPbig);
    } while(fPbig < 0 || fPbig > 1);
    if(fPbig == 1)
        do{
            printf("Please enter a value that is 200 and above\n");
            printf("Pag-Ibig: "); scanf("%lf", &fPbig);
        } while (fPbig < 200); // Min. voluntary contribution is P200
    else fPbig = 0;
    
    do{
        printf("\nPhilHealth: "); scanf("%lf", &fPhilHlth); printf("\n");
    } while(fPhilHlth < 0 || fPhilHlth > 1);
    
    pattern('~', 51);
    printf("               ADDITIONAL EXEMPTION\n\n");
    printf("             Type [0] if not applicable\n\n");
    do{
        printf("13 Month Pay: "); scanf("%lf", &fThirteen);
    } while (fThirteen < 0);
    printf("\n\n");
    
    pattern('~', 51);
    printf("                  [1] Yes [2] No\n\n");
    do{
        printf("Do you have other sources of income? "); scanf("%d",&source);
        printf("\n\n");
        if(source == 1)
        {
            printf("If you've encoded all incomes, type [0] to end loop.\n");
            while(fOther > 0){
                counter ++;
                printf("Income %d: ", counter); scanf("%lf", &fOther);
                fMonthly += fOther;
            }
            printf("\n");
        }
        else
            fOther = 0;
    } while (source < 1 || source > 2);
    
    //Computing for Monthly SSS and Pag-Ibig Contribution
    pattern('#', 51);
    if (fSocial == 0)
        fSocial = SSS(fMonthly) * 500 * 0.0363;  // Non-voluntary member pays 3.63% of the monthly credit
    else
        fSocial = SSS(fMonthly) * 500 * 0.11; // Voluntary member pays 11% of the monthly credit
    
    if (fPbig == 0)
        fPbig = PagIbig(fMonthly);
    
    fDeductions = fSocial + fPbig;
    fPersonal = personal(nKids);
    fOld = oldtax(fMonthly, fPersonal, fDeductions, fThirteen, fPhilHlth);
    
    printf("               UNDER 2017 TAX CODE\n\n");
    
    if (fOld<=0)
    { fOld = 0; printf("          Your don't have to pay a tax!\n"); printf("\n"); }
    else
    { printf("     Your annual income tax due is %.2f pesos\n", fOld); printf("\n"); }
    
    if (fMonthly * 12 > 250000)
    {
        fPersonal = 0;
        fNew = trainlaw(fMonthly, fDeductions, fThirteen, fPersonal, fPhilHlth);
        printf("                UNDER TRAIN LAW\n\n");
        printf("     Your annual income tax due is %.2f pesos\n", fNew); printf("\n");
        printf("                  YOU TAKE HOME\n\n");
        if(fNew>fOld) {
            printf("             Around 0 pesos annually"); printf("\n\n"); }
        else {
            printf("           Around %.2f pesos annually",fOld-fNew); printf("\n\n"); }
    }
    else
    {
        fNew = 0;
        printf("                UNDER TRAIN LAW\n\n");
        printf("           You're a minimum wage earner!"); printf("\n\n");
        printf("                  YOU TAKE HOME\n\n");
        printf("             Around %.2f pesos annually",fOld); printf("\n\n");
    }
    pattern('#', 51);
    return 0;
}
