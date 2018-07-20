SELECT film.title AS film_title FROM film
WHERE film.film_id in
(SELECT f.film_id FROM film f
 LEFT JOIN film_actor fa ON fa.film_id = f.film_id
 LEFT JOIN actor a ON a.actor_id = fa.actor_id
 WHERE a.first_name LIKE 'KIRSTEN'
 AND a.last_name LIKE 'PALTROW')
 AND film.film_id IN
 (SELECT f.film_id FROM film f
 LEFT JOIN film_actor fa ON fa.film_id = f.film_id
 LEFT JOIN actor a ON a.actor_id = fa.actor_id
 WHERE a.first_name LIKE 'WARREN'
 AND a.last_name LIKE 'NOLTE')
 ORDER BY film_title DESC