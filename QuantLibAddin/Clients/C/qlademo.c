
/*
 Copyright (C) 2004, 2005 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <Addins/C/qladdin.h>
#include <stdio.h>
#include <malloc.h>

int main() {
    double dividendYield = 0.00;
    double riskFreeRate = 0.06;
    double volatility = 0.20;
    double underlying = 36;
    double strike = 40;
    long timeSteps = 801;
    long exerciseDate = 43903;      // (13, March, 2020);
    long settlementDate = 43537;    // (13, March, 2019);
    char result[100];               // presently a dummy value

    OH_SET_LOGFILE("quantlib.log"); // specify log file
    OH_CONSOLE(1);                  // log messages to stdout
    OH_LOG_MESSAGE("begin example program");

    OH_LOG_MESSAGE(QL_VERSION());
    OH_LOG_MESSAGE(OH_VERSION());

    if (QL_BLACK_CONSTANT_VOL(
            "my_blackconstantvol", 
            settlementDate, 
            volatility, 
            "Actual360",
            result) != SUCCESS) {
        OH_LOG_MESSAGE("Error on call to QL_BLACK_CONSTANT_VOL");
        goto fail;
    }

    if (QL_BLACK_SCHOLES_PROCESS(
            "my_stochastic", 
            "my_blackconstantvol", 
            underlying, 
            "Actual360",
            settlementDate, 
            riskFreeRate, 
            dividendYield, 
            result) != SUCCESS) {
        OH_LOG_MESSAGE("Error on call to QL_BLACK_SCHOLES_PROCESS");
        goto fail;
    }

    if (QL_VANILLA_OPTION(
            "my_option",                    // option handle
            "my_stochastic",                // stochastic process handle
            "Put",                          // option type
            "Vanilla",                      // payoff type
            strike,                         // strike price
            "American",                     // exercise type
            exerciseDate,                   // exercise date
            settlementDate,                 // settlement date
            "JR",                           // engine type (jarrow rudd)
            timeSteps,                      // time steps
            result) != SUCCESS) {
        OH_LOG_MESSAGE("Error on call to QL_VANILLA_OPTION");
        goto fail;
    }

    OH_LOG_MESSAGE("high-level interrogation - after QL_VANILLA_OPTION");
    OH_LOG_OBJECT("my_option");

    if (QL_OPTION_SETENGINE(
            "my_option", 
            "AEQPB",   // AdditiveEQPBinomialTree
            801, 
            result) != SUCCESS) {
        OH_LOG_MESSAGE("Error on call to QL_OPTION_SETENGINE");
        goto fail;
    }

    OH_LOG_MESSAGE("high-level interrogation - after QL_OPTION_SETENGINE");
    OH_LOG_OBJECT("my_option");

    OH_LOG_MESSAGE("end example program");

    return 0;

fail:

    return 1;
}

