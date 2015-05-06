/*
 * Field.h
 *
 *  Created on: 04.05.2015
 *      Author: jentin
 */

#ifndef FIELD_H_
#define FIELD_H_

class Field {
public:
	Field();

	void setType(bool land);
	bool getType() const;

	int getTextureNumber() const;

	virtual ~Field();
private:
	bool land;
};

#endif /* FIELD_H_ */
