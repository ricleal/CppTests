/*
 * observer.h
 *
 *  Created on: Oct 27, 2013
 *      Author: leal
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

/**
 * Define an object that is the “keeper” of the data model and/or business logic (the Subject).
 * Delegate all “view” functionality to decoupled and distinct Observer objects.
 * Observers register themselves with the Subject as they are created.
 * Whenever the Subject changes, it broadcasts to all registered Observers that it has changed,
 * and each Observer queries the Subject for that subset of the Subject’s state
 * that it is responsible for monitoring.
 *
 * inspired from: http://sourcemaking.com/design_patterns/observer
 *
 */
#include <iostream>
#include <vector>

using namespace std;

class Observer;

/**
 * Subject
 * Going to spread the news to its subscribers / observers
 */
class Subject {
public:
	// Observer will register them selves using this command
	void registerObserver(Observer *obs) {
		listOfRegisteredObservers.push_back(obs);
	}
	void setNews(string news_) {
		news = news_;
		notify();
	}
	string getNews() {
		return news;
	}
	void notify();

private:
	vector<class Observer *> listOfRegisteredObservers; // 3. Coupled only to "interface"
	string news;
};

class Observer {
public:
	Observer(Subject *subject_) {
		subject = subject_;
		// Observers register themselves with the Subject
		subject->registerObserver(this);
	}
	virtual ~Observer(){}
	virtual void update() = 0;
protected:
	Subject *getSubject() {
		return subject;
	}
private:
	// 2. "dependent" functionality
	Subject *subject;
};

class HtmlObserver: public Observer {
public:
	HtmlObserver(Subject *mod) :
	Observer(mod) {}
	void update() {
		// 6. "Pull" information of interest
		string news = getSubject()->getNews();
		cout << "<html>" << news << "</html>" << '\n';
	}
};

class TextObserver: public Observer {
public:
	TextObserver(Subject *mod) :
	Observer(mod) {}
	void update() {
		// 6. "Pull" information of interest
		string news = getSubject()->getNews();
		cout << news << '\n';
	}
};


#endif /* OBSERVER_H_ */
