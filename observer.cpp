/*
 * observer.cpp
 *
 *  Created on: Oct 27, 2013
 *      Author: leal
 */

#include "observer.h"

using namespace std;


/**
 * Let's broacats the news to my Observers
 */
void Subject::notify() {
	for (size_t i = 0; i < listOfRegisteredObservers.size(); i++)
		listOfRegisteredObservers[i]->update();
}


int main_observer() {
	Subject subj;

	HtmlObserver htmlObs(&subj);
	TextObserver textObs(&subj);

	subj.setNews("This is the news 1");
	subj.setNews("This is the news 2");
}

