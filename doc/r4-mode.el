;; MC - 2013-2017
;; this is the start of an r4 emacs mode
;; which tries to simulate the proper r4 editor
;; Be Warned : the changes are *not* buffer dependent yet....

;; TODO: extend/improve the regexps...
(setq r4-keywords
      '((":[a-zA-Z0-9_\.-]+\\b" . 'r4-definition-face)
	("\\#[a-zA-Z\._]+\\b" . 'r4-data-face)
	("\'[a-zA-Z0-9_\.-]+\\b" . 'r4-pointer-face)
	("|.*$" . 'r4-comment-face)
	("\\^[a-zA-Z0-9_/\.-]+\\b" . 'r4-include-face)
	("\\b[\$|\%]?[0-9]+\\b" . 'r4-numbers-face)))

(define-derived-mode r4-mode fundamental-mode

  ;;    :main
  (make-face 'r4-definition-face)
  (set-face-foreground 'r4-definition-face "red")

  ;;    123 $123 %01010
  (make-face 'r4-numbers-face)
  (set-face-foreground 'r4-numbers-face "yellow")

  ;;     'ptr
  (make-face 'r4-pointer-face)
  (set-face-foreground 'r4-pointer-face "cyan")

  ;;      ^abc.txt
  (make-face 'r4-include-face)
  (set-face-foreground 'r4-include-face "yellow")

  ;;      #abc
  (make-face 'r4-data-face)
  (set-face-foreground 'r4-data-face "purple")

  ;;      | comment
  (make-face 'r4-comment-face)
  (set-face-foreground 'r4-comment-face "darkgray")

  ;;      "abc"
  (custom-set-faces
   '(font-lock-string-face ((t (:foreground "white")))))

  ;; set background to black
  (set-background-color "black")
  (set-foreground-color "green")

  (setq font-lock-defaults '(r4-keywords))
  (setq mode-name "R4"))
