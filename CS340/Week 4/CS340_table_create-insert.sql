/*
Connor Shields
CS 340
Project Step 3
5/2/2018
*/

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

INSERT INTO room (number)
VALUES
(200),
(201),
(202),
(203),
(204),
(205);

insert into provider (fname, lname, patients, specialty, room_number)
VALUES
('Andrew', 'Smith', 3, 'Surgery', 205),
('Kasey', 'Jones', 1, 'Radiology', 204),
('Jared', 'Sampang', 2, 'General', 203),
('Jeff', 'Goldblum', 1, 'Clinical Chaos', 202),
('William', 'Faulkner', 0, 'Stream of Consciousness', 201);

INSERT INTO patient (fname, lname, primary_provider, treatments_complete, active_status)
VALUES
('Henry', 'Henry', 1, 10, true),
('Jason', 'Goff', 1, 20, false),
('Alfred', 'Butler', 1, 14, true),
('Tom', 'Riddle', 2, 50, true),
('Blaine', 'Roberts', 3, 12, true),
('Simon', 'Richard', 3, 15, false),
('Dexter', 'Morgan', 4, 80, true);

INSERT INTO appointment (provID, patientID, cost, insurancePortion, patientPortion, status)
VALUES
(2, 1, 5000, 4000, 1000, 'SCHEDULED'),
(3, 1, 6000, 4800, 1200, 'BROKEN'),
(4, 7, 0, 0, 0,  'BROKEN');

INSERT INTO insurance_carrier (subscribers, name, coverage)
VALUES
(2, 'Aetna', 80),
(2, 'Metlife', 100);

INSERT INTO insurance_subscription(patID, insID)
VALUES
(1, 1),
(1, 2),
(2, 2),
(2, 1);