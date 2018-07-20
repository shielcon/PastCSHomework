SELECT film_id from film
WHERE film.length = (SELECT MAX(film.length) FROM film)
OR film.rental_duration = (SELECT MIN(film.rental_duration) FROM film);