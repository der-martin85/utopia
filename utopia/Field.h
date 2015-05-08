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
	void reset();

	void setType(bool land);
	void setMoist(bool moist);
	void setTrees(unsigned int trees);
	void setStone(unsigned int stone);
	void setGold(unsigned int gold);
	void setIron(unsigned int iron);
	void setCopper(unsigned int copper);
	void setCoal(unsigned int coal);
	void setOil(unsigned int oil);

	bool getType() const;
	bool getMoist() const;
	unsigned int getTrees() const;
	unsigned int getStone() const;
	unsigned int getGold() const;
	unsigned int getIron() const;
	unsigned int getCopper() const;
	unsigned int getCoal() const;
	unsigned int getOil() const;

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
