
(cl:in-package :asdf)

(defsystem "robot_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "RobotIns" :depends-on ("_package_RobotIns"))
    (:file "_package_RobotIns" :depends-on ("_package"))
    (:file "RobotPosition" :depends-on ("_package_RobotPosition"))
    (:file "_package_RobotPosition" :depends-on ("_package"))
  ))