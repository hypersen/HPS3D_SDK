
(cl:in-package :asdf)

(defsystem "hps_camera-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "PointCloudData" :depends-on ("_package_PointCloudData"))
    (:file "_package_PointCloudData" :depends-on ("_package"))
    (:file "distance" :depends-on ("_package_distance"))
    (:file "_package_distance" :depends-on ("_package"))
    (:file "measureData" :depends-on ("_package_measureData"))
    (:file "_package_measureData" :depends-on ("_package"))
  ))