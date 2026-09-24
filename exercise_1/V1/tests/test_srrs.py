import pytest

from src.main import RailwayReservationSystem


@pytest.fixture
def system():
    return RailwayReservationSystem()


def test_train_search(system):
    trains = system.search_trains("Delhi", "Lucknow")
    assert len(trains) == 1
    assert trains[0].train_id == "T101"


def test_passenger_registration(system):
    passenger = system.register_passenger("P001", "Asha")
    assert passenger.name == "Asha"
    assert "P001" in system.passengers


def test_ticket_booking_reduces_seat_count(system):
    system.register_passenger("P001", "Asha")
    booking = system.book_ticket("P001", "T101")

    assert booking.status == "CONFIRMED"
    assert system.seat_availability("T101") == 4


def test_ticket_cancellation_restores_seat(system):
    system.register_passenger("P001", "Asha")
    booking = system.book_ticket("P001", "T101")

    system.cancel_ticket(booking.booking_id)

    assert booking.status == "CANCELLED"
    assert system.seat_availability("T101") == 5


def test_booking_requires_registered_passenger(system):
    with pytest.raises(ValueError, match="not registered"):
        system.book_ticket("P999", "T101")


def test_booking_fails_when_train_has_no_seats(system):
    system.register_passenger("P001", "Asha")

    for i in range(5):
        system.register_passenger(f"P{i+10}", f"Passenger {i}")
        system.book_ticket(f"P{i+10}", "T101")

    with pytest.raises(ValueError, match="No seats"):
        system.book_ticket("P001", "T101")
