#include <stdio.h>
#include <stdlib.h>

// Define the structure for a polynomial term
struct Term {
    int coeff; // Coefficient
    int exp;   // Exponent
    struct Term* next; // Pointer to the next term
};

// Function prototypes
struct Term* createTerm(int coeff, int exp);
void insertTerm(struct Term** poly, int coeff, int exp);
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2);
void printPolynomial(struct Term* poly);

// Function to create a new term
struct Term* createTerm(int coeff, int exp) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coeff = coeff;
    newTerm->exp = exp;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term into the polynomial
void insertTerm(struct Term** poly, int coeff, int exp) {
    struct Term* newTerm = createTerm(coeff, exp);
    if (*poly == NULL || (*poly)->exp < exp) {
        newTerm->next = *poly;
        *poly = newTerm;
    } else {
        struct Term* current = *poly;
        while (current->next != NULL && current->next->exp > exp) {
            current = current->next;
        }
        if (current->exp == exp) {
            current->coeff += coeff; // Combine like terms
            free(newTerm); // Free the new term if it's combined
        } else {
            newTerm->next = current->next;
            current->next = newTerm;
        }
    }
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term* current1 = poly1;
    struct Term* current2 = poly2;

    while (current1 != NULL || current2 != NULL) {
        if (current1 == NULL) {
            insertTerm(&result, current2->coeff, current2->exp);
            current2 = current2->next;
        } else if (current2 == NULL) {
            insertTerm(&result, current1->coeff, current1->exp);
            current1 = current1->next;
        } else if (current1->exp > current2->exp) {
            insertTerm(&result, current1->coeff, current1->exp);
            current1 = current1->next;
        } else if (current1->exp < current2->exp) {
            insertTerm(&result, current2->coeff, current2->exp);
            current2 = current2->next;
        } else {
            insertTerm(&result, current1->coeff + current2->coeff, current1->exp);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return result;
}

// Function to print the polynomial
void printPolynomial(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    struct Term* current = poly;
    while (current != NULL) {
        printf("%dx^%d", current->coeff, current->exp);
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Main function
int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;

    // Inserting terms into the first polynomial (e.g., 3x^2 + 5x + 6)
    insertTerm(&poly1, 3, 2);
    insertTerm(&poly1, 5, 1);
    insertTerm(&poly1, 6, 0);

    // Inserting terms into the second polynomial (e.g., 4x^2 + 2x + 1)
    insertTerm(&poly2, 4, 2);
    insertTerm(&poly2, 2, 1);
    insertTerm(&poly2, 1, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);
    
    printf("Polynomial 2: ");
    printPolynomial(poly2);

    // Adding the two polynomials
    struct Term* result = addPolynomials(poly1, poly2);
    
    printf("Resultant Polynomial: ");
    printPolynomial(result);

    return 0;
}