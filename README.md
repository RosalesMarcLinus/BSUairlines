# BSUairlines

The BSU Airlines Ticket Booking System is a command-line application that allows customers to book flights and manage their bookings. Here's a brief overview of its functionalities:

**1. Customer Sign Up/Sign In**

- Customers can sign up by providing their name, username, password, age, contact number, and nationality. The provided information is stored in the "passenger.csv" file for future reference.

- Existing customers can sign in using their username and password.
  

**2. Check Promos**

- The system displays available promos stored in the "promos.csv" file. Each promo entry includes a description, destination, and ticket cost.

- Customers can choose to book a flight through a promo, which automatically assigns seats without seat selection.

- After selecting a promo, customers need to provide their name as the ticket holder and the flight number. These details are stored in the "passengerflights.csv" file.

- A summary of the booking, including the ticket holder's name, flight number, assigned seat, and ticket cost, is displayed.
  

**3. Book Flight**
   
- Customers can book flights by specifying their desired destination and the number of tickets they want to purchase.

- The system prompts the customer to specify the ticket holder's name.

- Available flights for the specified destination are displayed, showing seat availability for each flight.

- Customers can choose their preferred seat, and the ticket cost for the selected flight is shown.

- The ticket holder's name, flight number, assigned seat, and ticket cost are stored in the "passengerflights.csv" file.
  

**4. Available Flights**
   
- The system displays available flights and the number of available seats for each flight, read from the "availableflights.csv" file.

- Customers can book a flight if they find a suitable option.
  

**5. Cancellation of Flights**

- Customers can cancel their existing flights by providing their name.

- The system checks if the customer's name exists in the "passengerflights.csv" file.

- If the name is found, the ticket information (ticket holder's name, flight number, assigned seat, and ticket cost) is displayed.

- The customer can confirm if they want to proceed with the flight cancellation. If confirmed, the corresponding information is deleted from the "passengerflights.csv" file.


**6. About Page**
   
- The About Page displays information about the programmer or the development team.
