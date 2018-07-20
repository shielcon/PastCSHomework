CREATE TABLE client (
	id int(11) AUTO_INCREMENT,
	first_name varchar(255) NOT NULL,
	last_name varchar(255) NOT NULL,
	dob date NOT NULL,
    PRIMARY KEY(id),
    CONSTRAINT full_name UNIQUE (first_name, last_name)
) ENGINE=InnoDB;

CREATE TABLE employee (
	id int(11) AUTO_INCREMENT,
	first_name varchar(255) NOT NULL,
	last_name varchar(255) NOT NULL,
	dob date NOT NULL,
	date_joined date NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT full_name UNIQUE (first_name, last_name)
) ENGINE=InnoDB;

CREATE TABLE project (
	id int(11) NOT NULL AUTO_INCREMENT,
	cid int(11),
	name varchar(255) NOT NULL UNIQUE,
	notes TEXT,
    PRIMARY KEY(id),
    FOREIGN KEY(cid) REFERENCES client(id)
)ENGINE=InnoDB;

CREATE TABLE works_on (
	eid int(11) NOT NULL,
	pid int(11) NOT NULL,
	start_date date NOT NULL,
	PRIMARY KEY (eid, pid),
    FOREIGN KEY(eid) REFERENCES employee(id),
    FOREIGN KEY(pid) REFERENCES project(id)
) ENGINE=InnoDB;