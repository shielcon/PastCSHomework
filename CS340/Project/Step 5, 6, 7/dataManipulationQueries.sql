/*
Connor Shields and Gabriel Janzen
CS 340 - Data Manipulation Queries
5/24/2018

*/

/* item 5-8 */
SELECT * FROM `c_variety`;
SELECT * FROM `c_roaster`;
SELECT * FROM `c_roast`;
SELECT * FROM `c_coffee`;
SELECT * FROM `c_origin`;

/* item 9 can show records from many-to-many */
SELECT * FROM `c_coffee` c
INNER JOIN `c_coffee_variety cv
ON cv.`coffee_id` = c.`coffee_id`
INNER JOIN `c_variety` var
ON var.`variety_id` = cv.`variety_id`;

/* item 10 - all records from one-to-many */
SELECT * FROM `c_coffee c`,
INNER JOIN `c_roast` r ON c.roaster = r.`roast_id`;

/*items 11-14 (insertions) */

INSERT INTO `c_coffee` (name, roaster, roast, description)
VALUES ([nameinput], [roasterID], [roastID], [description]);

INSERT INTO `c_roaster` (`name`, `city`, `state`)
VALUES ([nameInput], [cityInput], [stateInput]);

INSERT INTO `c_roast` (`roast`)
VALUES ([roastInput]);

INSERT INTO c_origin (`country`, `continent`)
VALUES ([countryInput], [continentInput]);

/*items 15-18 (removals) */

DELETE FROM `c_coffee`
WHERE `c_coffee`.`coffee_id` = [coffeeInput];

DELETE FROM `c_roast`
WHERE `c_roast`.`roast_id` = [roastInput];

DELETE FROM `c_roaster`
WHERE `c_roaster`.`roaster_id` = [roasterInput];

DELETE FROM `c_origin`
WHERE `c_origin`.`origin_id` = [originInput];


/*19 - Can associate any rows between
E1(coffee) and E2(variety) in the many-to-many relationship*/

INSERT INTO `c_coffee_variety`
(`coffee_id`, `variety_id`)
VALUES ([coffeeInput], [varietyInput]);

/*20 - Can de-associate any rows between E1
and E2 in the many-to-many relationship*/
DELETE FROM `c_coffee_variety`
WHERE `coffee_id` = [coffeeInput]
AND `variety_id` = [varietyInput];

/*21 - can change association of rows between E2 and E2
(I'm working on the assumption that this is a typo and was
supposed to be E1 and E2)*/

UPDATE `c_coffee_variety`
SET `variety_id` = [varietyInput]
WHERE `coffee_id` = [coffeeInput];

/*22 - Can associate any rows between E1 and E3(roast)*/

UPDATE `c_coffee`
SET `roaster` = [roastInput]
WHERE `coffee_id` = [coffeeInput];

/*23 - not possible with this schema */

/* 24 - Can search on at least one Entity's one attribute */

SELECT * FROM `c_coffee`
WHERE `name` LIKE CONCAT('%', [coffeeInput], '%');

/*26 - Can update details for E1 */

UPDATE `c_coffee`
SET `name` = [nameInput]
WHERE `coffee_id` = [chosenCoffee];

/*27*/

UPDATE `c_roast`
SET `roast` = [roastInput]
WHERE `roast_id` = [chosenRoast];

/*28*/

UPDATE `c_roaster`
SET `name` = [nameInput]
WHERE `roaster_id` = [roaster];

/*29*/

UPDATE `c_origin`
SET `country` = [countryInput]
WHERE `origin_id` = [chosenOrigin];

