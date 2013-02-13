(define (sigma term a next b) ;; SICP
  (if (> a b)
    0
    (+ (term a)
       (sigma term (next a) next b))))

(define (pi)
  (define (pi-sum a b)
    (define (pi-term x)
      (/ 1.0 (* x (+ x 2))))
    (define (pi-next x)
      (+ x 4))
    (* 8 (sigma pi-term a pi-next b)))
  (pi-sum 1 10000))
