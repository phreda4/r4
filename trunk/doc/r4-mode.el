;; MC - 2013
;; this is the start of an r4 emacs mode
;; which tries to simulate the proper r4 editor
;; when the keyboard just won't work...
;; 
;; Be Warned : the changes are *not* buffer dependent yet....

;; extend/improve the regexps...
(setq r4-keywords
      '(("^:[a-zA-Z0-9_\.-]+" . 'r4-definition-face)
	("\'[a-zA-Z0-9_\.-]+" . 'r4-pointer-face)
	("|.*$" . 'r4-comment-face)
	("\\#[a-zA-Z\._]+ " . 'r4-data-face)
	("\\^.*$" . 'r4-include-face)
	("\\b[0-9]+\\b" . 'r4-numbers-face)))

(define-derived-mode r4-mode fundamental-mode

  (make-face 'r4-numbers-face)
  (set-face-foreground 'r4-numbers-face "yellow")

  (make-face 'r4-pointer-face)
  (set-face-foreground 'r4-pointer-face "cyan")

  (make-face 'r4-include-face)
  (set-face-foreground 'r4-include-face "yellow")

  (make-face 'r4-definition-face)
  (set-face-foreground 'r4-definition-face "red")

  (make-face 'r4-data-face)
  (set-face-foreground 'r4-data-face "purple")

  (make-face 'r4-comment-face)
  (set-face-foreground 'r4-comment-face "darkgray")

  (custom-set-faces
   '(font-lock-string-face ((t (:foreground "white")))))

  ;; set background to black

  (set-background-color "black")
  (set-foreground-color "green")

  (setq font-lock-defaults '(r4-keywords))
  (setq mode-name "R4"))

