SELECT a.first_name, a.last_name FROM actor a
where a.actor_id NOT IN 
(SELECT a.actor_id from actor a 
LEFT JOIN film_actor fa on fa.actor_id = a.actor_id 
LEFT JOIN film f ON f.film_id = fa.film_id 
LEFT JOIN film_category fc on fc.film_id = f.film_id 
LEFT JOIN category c ON c.category_id = fc.category_id 
WHERE c.name LIKE 'Sci-Fi');