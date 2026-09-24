from dataclasses import dataclass
from typing import Dict, List, Optional


@dataclass
class Train:
    train_id: str
    name: str
    source: str
    destination: str
    total_seats: int
    available_seats: int


@dataclass
class Passenger:
    passenger_id: str
    name: str


@dataclass
class Booking:
    booking_id: str
    passenger_id: str
    train_id: str
    status: str = "CONFIRMED"


class RailwayReservationSystem:
    """Small in-memory SRRS V1 implementation."""

    def __init__(self) -> None:
        self.trains: Dict[str, Train] = {
            "T101": Train("T101", "InterCity Express", "Delhi", "Lucknow", 5, 5),
            "T202": Train("T202", "Ganga Express", "Prayagraj", "Varanasi", 4, 4),
            "T303": Train("T303", "Shatabdi", "Delhi", "Kanpur", 3, 3),
        }
        self.passengers: Dict[str, Passenger] = {}
        self.bookings: Dict[str, Booking] = {}
        self._booking_counter = 1

    def search_trains(self, source: str, destination: str) -> List[Train]:
        return [
            train for train in self.trains.values()
            if train.source.lower() == source.lower()
            and train.destination.lower() == destination.lower()
        ]

    def seat_availability(self, train_id: str) -> int:
        train = self._get_train(train_id)
        return train.available_seats

    def register_passenger(self, passenger_id: str, name: str) -> Passenger:
        if not passenger_id or not name.strip():
            raise ValueError("Passenger ID and name are required.")
        if passenger_id in self.passengers:
            raise ValueError("Passenger already registered.")

        passenger = Passenger(passenger_id, name.strip())
        self.passengers[passenger_id] = passenger
        return passenger

    def book_ticket(self, passenger_id: str, train_id: str) -> Booking:
        if passenger_id not in self.passengers:
            raise ValueError("Passenger is not registered.")

        train = self._get_train(train_id)
        if train.available_seats <= 0:
            raise ValueError("No seats available.")

        booking_id = f"B{self._booking_counter:04d}"
        self._booking_counter += 1

        train.available_seats -= 1
        booking = Booking(booking_id, passenger_id, train_id)
        self.bookings[booking_id] = booking
        return booking

    def cancel_ticket(self, booking_id: str) -> Booking:
        if booking_id not in self.bookings:
            raise ValueError("Booking not found.")

        booking = self.bookings[booking_id]
        if booking.status == "CANCELLED":
            raise ValueError("Booking is already cancelled.")

        booking.status = "CANCELLED"
        self.trains[booking.train_id].available_seats += 1
        return booking

    def _get_train(self, train_id: str) -> Train:
        if train_id not in self.trains:
            raise ValueError("Train not found.")
        return self.trains[train_id]


def demo() -> None:
    system = RailwayReservationSystem()
    system.register_passenger("P001", "Asha")
    booking = system.book_ticket("P001", "T101")

    print("SRRS v1.0")
    print(f"Booking created: {booking.booking_id}")
    print(f"Seats remaining on T101: {system.seat_availability('T101')}")


if __name__ == "__main__":
    demo()
