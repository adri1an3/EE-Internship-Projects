/*
File: Queue.h
Author: Adrian Jimenez
Description: Declare queue class functionality and define in the same header
to avoid template-related errors.
Date: October 25, 2025
*/

#pragma once
#ifndef QUEUE
#define QUEUE
#include <stdexcept>

template <typename T>
class Queue {
private:
	enum : int { //256 is the maxQueue to read large file lines.
		//const global ints were made private enums to avoid definition errors. 
		MAXQUEUE = 256,
		QFULL = MAXQUEUE,
		QEMPTY = 0,
		EMPTY = -1
	};

	T items[MAXQUEUE]; //Template of items array, where Maxqueue is the array's size.
	int head; //head or first in queue
	int tail; //tail or last in queue

public:
	//Functionality
	Queue(); //Initializes the Queue.

	bool enqueue(T item); //Add an item to the end of the queue
	T dequeue(); //Removes a value from the front to the queue and returns it.
	T peek(); //Returns the value at the front of the queue without removing it
	bool isEmpty(); //Returns true if the queue is empty and false otherwise.
	bool isFull(); //Returns true if the queue is full and false otherwise.
	void clear(); //Clears the queue and initializes it's variables.

};

template<typename T>
inline Queue<T>::Queue()
{
	this->head = 0;
	this->tail = 0; //free up queue
}

template<typename T>
inline bool Queue<T>::enqueue(T item)
{
	if (this->isFull())
		return false; //If queue is full, do not add item to queue
	else
	{
		this->items[this->tail] = item; //store item at tail index of queue
		tail = (this->tail + 1) % MAXQUEUE; //circular queue functionality, modulus restarts index at beginnig
		return true;
	}
}

template<typename T>
inline T Queue<T>::peek() {
	if (this->isEmpty())
		throw std::out_of_range("Queue is empty");
	else
		return this->items[head]; //peek at first item on list
}

template<typename T>
inline T Queue<T>::dequeue()
{
	if (this->isEmpty())
		throw std::runtime_error("Queue is empty");
	else
	{
		T item = this->items[head];
		this->head = (this->head + 1) % MAXQUEUE; //move queue forward, head index restarting at 0 when max is met
		return item;

	}
}

template<typename T>
inline bool Queue<T>::isEmpty()
{
	return this->head == this->tail; //if head and tail index are the same, queue is empty
}

template<typename T>
inline bool Queue<T>::isFull()
{
	return ((tail + 1) % MAXQUEUE) == head; //check if tail has reached the front of queue
}

template<typename T>
inline void Queue<T>::clear() {
	this->head = 0;
	this->tail = 0; //set tail and head indexes to zero
}

#endif