CREATE TABLE room(
number int(11) NOT NULL UNIQUE,
PRIMARY KEY(number)
) ENGINE=InnoDB;

CREATE TABLE provider(
provider_id int(11) NOT NULL AUTO_INCREMENT,
fname varchar(255) NOT NULL,
lname varchar(255) NOT NULL,
patients int(11) NOT NULL DEFAULT 0,
specialty varchar(255) NOT NULL DEFAULT 'General',
room_number int(11) NOT NULL UNIQUE,
PRIMARY KEY(provider_id),
FOREIGN KEY(room_number) REFERENCES room(number)
) ENGINE=InnoDB;

CREATE TABLE patient (
id int(11) NOT NULL AUTO_INCREMENT,
fname varchar(255) NOT NULL,
lname varchar(255) NOT NULL,
primary_provider int(11) NOT NULL,
treatments_complete int(11) NOT NULL DEFAULT 0,
active_status bool NOT NULL DEFAULT FALSE,
PRIMARY KEY(id),
FOREIGN KEY(primary_provider) REFERENCES provider(provider_id)
) ENGINE = InnoDB;

CREATE TABLE appointment (
apptID int(11) NOT NULL AUTO_INCREMENT,
provID int(11) NOT NULL,
patientID int(11) NOT NULL,
cost int(11) NOT NULL DEFAULT 0,
insurancePortion int(11) NOT NULL DEFAULT 0,
patientPortion int(11) NOT NULL DEFAULT 0,
status enum('SCHEDULED', 'COMPLETE', 'BROKEN') NOT NULL DEFAULT 'SCHEDULED',
PRIMARY KEY(apptID),
FOREIGN KEY(provID) REFERENCES provider(provider_id),
FOREIGN KEY(patientID) REFERENCES patient(id)
) ENGINE=InnoDB;

CREATE TABLE insurance_carrier (
carrier_ID int(11) NOT NULL AUTO_INCREMENT,
subscribers int(11) NOT NULL DEFAULT 0,
name varchar(255) NOT NULL,
coverage int(11) NOT NULL DEFAULT 0,
PRIMARY KEY(carrier_ID)
) ENGINE=InnoDB;

CREATE TABLE insurance_subscription (
patID int(11) NOT NULL,
insID int(11) NOT NULL,
FOREIGN KEY(patID) REFERENCES patient(ID),
FOREIGN KEY(insID) REFERENCES insurance_carrier(carrier_ID)
  )ENGINE=InnoDB;

DESCRIBE room;
DESCRIBE provider;
DESCRIBE patient;
DESCRIBE appointment;
DESCRIBE insurance_carrier;
DESCRIBE insurance_subscription