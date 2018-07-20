/*
Connor Shields and Gabriel Janzen
CS 340 - Data Definition Queries
5/24/2018

No changes were made to these queries,as there were no
recommended changes in the feedback

*/

Data Definition Queries 
 CREATE TABLE `c_roaster` (
 `roaster_id` int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
 `name` varchar(100) NOT NULL,`city` varchar(100) NOT NULL,
 `state` varchar(100) NOT NULL ) 
 ENGINE=InnoDB DEFAULT CHARSET=latin1; 
 
 CREATE TABLE `c_roast` ( 
 `roast_id` int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
 `roast` varchar(11) NOT NULL ) 
 ENGINE=InnoDB DEFAULT CHARSET=latin1; 
 
 
CREATE TABLE `c_coffee` ( 
`coffee_id` int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
`name` varchar(100) NOT NULL,`roaster` int(11) NOT NULL,
`roast` int(11) NOT NULL,`description` varchar(255) DEFAULT NULL,
FOREIGN KEY (`roaster`) REFERENCES `c_roaster`(`roaster_id`) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (`roast`) REFERENCES `c_roast`(`roast_id`) ON DELETE CASCADE ON UPDATE CASCADE ) 
ENGINE=InnoDB DEFAULT CHARSET=latin1; 
 
 
CREATE TABLE `c_origin` ( 
`origin_id` int(11) 
PRIMARY KEY AUTO_INCREMENT NOT NULL,
`country` varchar(100) NOT NULL,
`continent` varchar(100) NOT NULL ) 
ENGINE=InnoDB DEFAULT CHARSET=latin1; 
 
 
CREATE TABLE `c_variety` ( 
`variety_id` int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
`name` varchar(100) NOT NULL,
`description` varchar(255) DEFAULT NULL ) 
ENGINE=InnoDB DEFAULT CHARSET=latin1; 
 

 CREATE TABLE `c_coffee_origin` ( 
 `coffee_id` int(11) NOT NULL,
 `origin_id` int(11) NOT NULL,
 FOREIGN KEY (`coffee_id`) REFERENCES `c_coffee`(`coffee_id`) ON DELETE CASCADE ON UPDATE CASCADE,
 FOREIGN KEY (`origin_id`) REFERENCES `c_origin`(`origin_id`) ON DELETE CASCADE ON UPDATE CASCADE ) 
 ENGINE=InnoDB DEFAULT CHARSET=latin1; 
 
 
CREATE TABLE `c_coffee_variety` ( 
`coffee_id` int(11) NOT NULL DEFAULT '1',
`variety_id` int(11) NOT NULL,
FOREIGN KEY (`coffee_id`) REFERENCES `c_coffee`(`coffee_id`) ON DELETE CASCADE ON UPDATE CASCADE,
FOREIGN KEY (`variety_id`) REFERENCES `c_variety`(`variety_id`) ON DELETE CASCADE ON UPDATE CASCADE ) 
ENGINE=InnoDB DEFAULT CHARSET=latin1;   

INSERT INTO `c_roast` (`roast_id`,`roast`)  
VALUES (1,'light'),(2,'medium'),(3,'medium-dark'),(4,'dark'); 
INSERT INTO `c_roaster` (`roaster_id`,`name`,`city`,`state`) 
VALUES (1,'keyboard','seattle','wa'),(2,'behemoth','portland','or'),(3,'unicorn','corvallis','or'),(4,'portrait','salem','or'); 
 
 
INSERT INTO `c_origin` (`origin_id`,`country`,`continent`) 
VALUES (1,'kenya','africa'),(2,'brazil','south america'),(3,'ethipoia','africa'),(4,'india','asia'); 
 INSERT INTO `c_variety` (`variety_id`,`name`,`description`) 
 VALUES (1,'arabica','most common variety'),(2,'burbon',NULL),(3,'liberica','bright,lemon flavor'),(4,'geisha',NULL); 

 INSERT INTO `c_coffee` (`coffee_id`,`name`,`roaster`,`roast`,`description`) 
 VALUES (1,'good morning',1,4,'wake up your morning'),(2,'espresso',2,4,'the finest espresso'),(3,'bicicle',3,1,'like flying through clouds'),(4,'golden flower',3,2,'simply amazing'),(5,'pitch black',4,4,'the darkest roast you will ever have'); 
 INSERT INTO `c_coffee_origin` (`coffee_id`,`origin_id`)  
 VALUES (1,3),(2,4),(3,1),(4,1),(5,2); 
 INSERT INTO `c_coffee_variety` (`coffee_id`,`variety_id`)  
 VALUES (1,3),(1,4),(3,2),(4,3),(5,1); 