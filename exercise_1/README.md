# Secure Railway Reservation System (SRRS) — Python Starter Package

This starter package is designed for the Software Security course.

It provides three progressively evolving Python versions of a small Railway
Reservation System. The application is intentionally simple: the focus of the
course is software security, Git/GitHub, code review, testing and DevSecOps,
not building a production railway platform.

## Versions

| Package | Application version | Main functionality |
|---|---|---|
| V1 | SRRS v1.0 | Train search, seat availability, passenger registration, booking, cancellation |
| V2 | SRRS v1.1 | V1 + passenger booking history |
| V3 | SRRS v1.2 | V2 + payment/refund interface |

The version progression follows the case-study evolution in the course
DevSecOps laboratory. Authentication/roles and later CI/CD controls are
introduced separately during the course.

## Directory structure

```text
SRRS-Python-Starter/
├── README.md
├── V1/
│   ├── src/
│   ├── tests/
│   ├── docs/
│   ├── requirements.txt
│   └── README.md
├── V2/
│   ├── src/
│   ├── tests/
│   ├── docs/
│   ├── requirements.txt
│   └── README.md
└── V3/
    ├── src/
    ├── tests/
    ├── docs/
    ├── requirements.txt
    └── README.md
```

## Student use in Unit 1

For Unit 1, students should begin with **V1** as the instructor-provided
baseline. They should not modify the instructor master package directly.

The intended workflow is:

1. Copy/clone the V1 starter application.
2. Create a personal GitHub repository.
3. Commit the V1 baseline.
4. Create an Issue for the requested functional change.
5. Create a feature branch.
6. Implement the Unit 1 change.
7. Commit and push the change.
8. Open a Pull Request.
9. Perform peer review.
10. Respond to review comments.
11. Merge the approved change.

V2 and V3 are included as controlled future application baselines so that the
same software can be progressively used later in the course.

## Running a version

From inside a version directory:

```sh
pip install -r requirements.txt
pytest -q
python -m src.main
```

No real credentials, external services or production data are required.
