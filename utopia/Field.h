/*
 * Field.h
 *
 *  Created on: 04.05.2015
 *      Author: Martin Ringwelski
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
	bool moist;			// Used to determine deep water or moist ground
	unsigned int trees;
	unsigned int stone;
	unsigned int gold;
	unsigned int iron;
	unsigned int copper;
	unsigned int coal;
	unsigned int oil;
};

#endif /* FIELD_H_ */
