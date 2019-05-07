
(cl:in-package :asdf)

(defsystem "hps_camera-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "camera" :depends-on ("_package_camera"))
    (:file "_package_camera" :depends-on ("_package"))
  ))